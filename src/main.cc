#include <cv.h>
#include <highgui.h>

#include <iostream>
#include <string>

#include "common.hh"
#include "util.hh"

int main( int argc, char** argv )
{
	Scene scene;
	scene.add_renderable(make_renderable(new Sphere(Vector(0, 2.5, 50), 2.5), new LambertianSurfaceProperty()));

	scene.add_renderable(make_renderable(
				new Sphere(Vector(-2.5, 2.5, 50), 3),
				new MonoGlowingSurfaceProperty()
				));


	Camera camera(Vector(0, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0),
			10.0, 4.0, 3.0,
			320, 240);

	RayTracer ray_tracer;
	shared_ptr<Image> image = ray_tracer.render(scene, camera);
	printf("1\n");
	Mat mat = image_to_mat(*image);
	printf("2\n");

	std::string window_name = "Hello world";
	namedWindow(window_name, CV_WINDOW_AUTOSIZE );
	imshow(window_name, mat);

	waitKey(0);
	return 0;
}
