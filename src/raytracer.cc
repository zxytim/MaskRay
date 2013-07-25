/**
 *@file: raytracer.cc
 *@date: Thu Jun 27 14:18:05 2013 +0800
 *@author: Xinyu Zhou <zxytim[at]gmail[dot]com>
 */


#include "raytracer.hh"
#include "intensity.hh"
#include <queue>
#include <thread>
#include <mutex>
#include "math.hh"
#include "util.hh"
#include <cv.h>
#include <highgui.h>
#include <string>
#include <algorithm>

#include <sys/time.h>

//#include <pthread.h>

using namespace std;

/**
 *@brief:   change intensity into color.
 */

static Color intensity_to_color(const Intensity &intensity)
{
	return Color(intensity.r, intensity.g, intensity. b);
}
/**
 *@brief:   clamp to 1.
 */
real_t clamp(real_t x) { return x < 0 ? x : x > 1 ? 1 : x; }

/**
 *@brief:   clamp intensity to ( 1 , 1 , 1 ).
 */
Intensity clamp(const Intensity &i) {
	return Intensity(clamp(i.r), clamp(i.g), clamp(i.b));
}

/**
 *@brief:   clamp color to ( 1 , 1 , 1 ).
 */
Color clamp(const Color &i) {
	return Color(clamp(i.r), clamp(i.g), clamp(i.b));
}

/**
 *@brief:   average input image.
 */
static void average_image(Image *input, real_t denominator, Image *output) {
	assert(input->size() == output->size());
	for (int i = 0, size = input->size(); i < size; i ++)
		output->data[i] = input->data[i] / denominator;
}


int RayTracer::ThreadTaskScheduler::fetch_task(std::vector<Ray> &task) {
	static std::mutex lock;
	lock.lock();
	{
		int start = cur_task,
			end = cur_task + n_ray_cast,
			size = camera.resol_x * camera.resol_y;

		if (end >= size) end = size;
		if (start >= size || start == end) {
			working = false;
			lock.unlock();
			return NO_TASK;
		}

		task.resize(end - start);
		for (int i = start; i < end; i ++) {
			int x = i / camera.resol_y;
			int y = i % camera.resol_y;
			task[i - start] = camera.emit_ray(x, y);
		}
	}
	lock.unlock();

	int ret = cur_task;
	cur_task += n_ray_cast;
	return ret;
}

void RayTracer::ThreadTaskScheduler::report_task(const std::vector<Intensity> &intensity, int tid) {
	int size = camera.resol_x * camera.resol_y;

	int end = min(tid + n_ray_cast, size);
	if ((end - tid) != (int)intensity.size())
		printf("%d %d\n", end - tid, (int)intensity.size());

	if ((end - tid) != (int)intensity.size())
		printf("end - tid: %d, intensity.size(): %d, n_ray_cast: %d\n",
				end - tid, (int)intensity.size(), n_ray_cast);
	assert((end - tid) == (int)intensity.size());
	for (int i = tid; i < end; i ++)
		image->data[i] += intensity_to_color(intensity[i - tid]);
}

void RayTracer::worker(ThreadTaskScheduler *tts) {
	std::vector<Ray> task;
	std::vector<Intensity> intensity;
	while (tts->working) {
		int tid = tts->fetch_task(task);
		if (tid == ThreadTaskScheduler::NO_TASK)
			continue;

		intensity.resize(task.size());

		for (size_t i = 0; i < task.size(); i ++)
			intensity[i] = trace(task[i]);

		tts->report_task(intensity, tid);
	}
}

RayTracer::ThreadTaskScheduler::ThreadTaskScheduler(Camera &camera, Image *image, int n_ray_cast) :
	camera(camera), image(image), n_ray_cast(n_ray_cast)
{
	cur_task = 0;
	working = true;
}

/**
 *@brief:  threading control, then call tracer.
 */

void RayTracer::naive_worker(Camera &camera, Image *image) {
	static std::mutex lock;
	int size = image->size();
	while (naive_worker_working) {
		int x, y;
		lock.lock();
		if (naive_worker_cur_pos == size) {
			naive_worker_working = false;
			lock.unlock();
			break;
		} else {
			if (naive_worker_cur_pos >= size)
				printf("!!!!%d\n", naive_worker_cur_pos);
			x = naive_worker_cur_pos / image->height;
			y = naive_worker_cur_pos % image->height;
			naive_worker_cur_pos ++;
		}
		lock.unlock();
		image->data[x * image->height + y] += intensity_to_color(trace(camera.emit_ray(x, y)));
	}
}

/**
 *@brief:   iterate call tracer.
 */
void RayTracer::iterate(Camera &camera, Image *image)
{
	int nworker = conf.N_THREDED_WORKER;
	// TODO: fetch #cpu
	if (nworker == -1)
		nworker = 4;


#if 1
	// naive worker
	auto threads = new std::thread[nworker];

	naive_worker_working = true;
	naive_worker_cur_pos = 0;

	for (int i = 0; i < nworker; i ++) {
		threads[i] = std::thread([&]{naive_worker(camera, image);});
	}

	for (int i = 0; i < nworker; i ++) {
		threads[i].join();
	}

	delete [] threads;

	return;
#else

	auto threads = new std::thread[nworker];
	ThreadTaskScheduler *tts = new ThreadTaskScheduler(camera, image);

	for (int i = 0; i < nworker; i ++) {
		threads[i] = std::thread([&]{worker(tts);});
		//#define SET_CPU_AFFINITY
#ifdef SET_CPU_AFFINITY
		cpu_set_t mask;
		CPU_ZERO(&mask);
		CPU_SET(i, &mask);
		if (pthread_setaffinity_np(threads[i].native_handle(), sizeof(mask), &mask) < 0) {

			perror("pthread_setaffinity_np");
		}
#endif
	}

	for (int i = 0; i < nworker; i ++) {
		threads[i].join();
	}

	delete [] threads;
	delete tts;
	return;
#endif
}

/**
 *@brief:   render the scene.
 */

Image * RayTracer::render(Scene &scene, Camera &camera)
{
	printf("start rendering ...\n");
	this->scene = &scene;

	Image *image = new Image(camera.resol_x, camera.resol_y),
		  *image_accum = (new Image(camera.resol_x, camera.resol_y));

	conf.print();
	string window_name = "Intermediate Image";
	cv::namedWindow(window_name, CV_WINDOW_AUTOSIZE);

	long long start_time = get_time();
	long long last_time = start_time;
	for (int i = 0; i < conf.N_ITER; i ++) {
		iterate(camera, image_accum);

		long long cur_time = get_time();
		printf("iteration %5d, speed: ave %dms, last: %dms, tot: %lldms, %lld ray/s\r",
				i, (int)((cur_time - start_time) / (i + 1)),
				(int)(cur_time - last_time),
				cur_time - start_time,
				(long long)(image->size()) * (i + 1) * 1000 / (cur_time - start_time) );
		fflush(stdout);
		last_time = cur_time;

		average_image(image_accum, i + 1, image);
#if 1
		cv::Mat mat = image_to_mat(*image);
		// show image
		if (i % conf.N_ITER_SHOW_IMAGE == 0) {
			cv::imshow(window_name, mat);
			cv::waitKey(1);
		}

		if (i % conf.N_ITER_WRITE_IMAGE == 0) {
			cv::imwrite(conf.IMAGE_NAME + "." + conf.IMAGE_FORMAT, mat);
		}
#endif
	}

	printf("\n");
	delete image_accum;
	return image;
}

/**
 *@brief:   call do_trace to tracing a ray.
 */
Intensity RayTracer::trace(const Ray &ray)
{
	return do_trace(ray, conf.TRACE_DEPTH_MAX);
}

/**
 *@brief:   get closest collision point.
 */

IntersectInfo * RayTracer::get_closest_intersection(const Ray &ray)
{
	real_t min_dist = 1e100;
	IntersectInfo * ii = nullptr;

	for (auto renderable: scene->renderable) {
		auto rst = renderable->intersect(ray);
		if (rst == nullptr)
			continue;
		real_t dist = rst->get_dist();
		if (dist < min_dist)
		{
			min_dist = dist;
			if (ii) delete ii;
			ii = rst;
		}
		else delete rst;
	}

	return ii;
}

/**
 *@brief:   tracer.
 *
 *tracer will stop if depth = 0.
 */

Intensity RayTracer::do_trace(const Ray &incident, int depth)
{
	IntersectInfo *inter = get_closest_intersection(incident);
	if (inter == nullptr) {
		delete inter;
		return Intensity(0, 0, 0); // black
	}

	Renderable *renderable = inter->renderable;

	Intensity texture = renderable->texture_mapper->get_texture(*inter);
	Intensity emission = renderable->surface_property->get_emission(*inter);

	if (incident.energy < conf.STOP_ENERGY_THRESHOLD || depth == 0) {
		delete inter;
		return emission;
	}

#if 0
	// Russian Roulette
	real_t prob = max(texture.r, max(texture.g, texture.b));
	if (depth > 5 || !prob) {
		if (random.rand_real() < prob)
			texture = texture / prob;
		else
			return emission;
	}
#endif

	Ray ray = inter->ray_bounce(incident);
	ray.o += ray.dir * EPS;


	Intensity ret(0, 0, 0);

	ret = do_trace(ray, depth - 1) * texture;
	ret = ret + emission;

	// FIXME: energy not used
	delete inter;
	return ret;

	// TODO:
	//		MATERIAL
	//		MEDIA
	//		BRDFs
}


/**
 * vim: syntax=cpp11 foldmethod=marker
 */

