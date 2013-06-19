#include <cv.h>
#include <highgui.h>

#include <iostream>
#include <string>

#include "common.hh"
#include "util.hh"

int main( int argc, char** argv )
{
	Scene scene;
#if 1
	// glowing ball 0
	scene.add_renderable(make_renderable("glowing ball", new Sphere(Vector(0, 3, 0), 0.5), new MonoGlowingSurfaceProperty(Intensity(0.9, 0.9, 0.9)), new MonoTextureMapper(Intensity(0.1, 0.1, 0.1))));

	scene.add_renderable(make_renderable("glass ball", new Sphere(Vector(1.0, 2.0, 0), 0.5), new GlassSurfaceProperty(), new MonoTextureMapper(Intensity(0.8, 1.0, 0.7)), new Material(1.5)));

	// chrome ball
	scene.add_renderable(make_renderable("chrome ball", new Sphere(Vector(-1.1, 2.8, 0), 0.5), new ChromeSurfaceProperty(), new MonoTextureMapper(Intensity(0.8, 0.8, 0.8))));
#endif

#if 0
	// glowing balls
	for (int i = 0; i < 5; i ++)
		for (int j = 0; j < 5; j ++) {
			real_t x = -1.6 + i * 0.25,
				   y = 0.8 + j * 0.25;
			real_t sp_r = sin(log(1 + i / 5.0)) / 1.2,
				   sp_g = cos(log(1 + j / 5.0)) / 1.2,
				   sp_b = sin(log((5 - i + j) / 5.0 + 1)) / 1.2;

			SurfaceProperty *sp;
			TextureMapper *tm;
			/*
			if ((i + j) & 1) {
				sp = new MonoGlowingSurfaceProperty(Intensity(sp_r, sp_g, sp_b));
				tm = new MonoTextureMapper(Intensity(0.1, 0.1, 0.1));
			} else {
				sp = new LambertianSurfaceProperty();
			}
			*/
			real_t ratio = (5 - i) * (j + 1) / 25.0;
			sp = new MonoGlowingLambertianSurfaceProperty(Intensity(sp_r * ratio, sp_g * ratio, sp_b * ratio));
			tm = new MonoTextureMapper(Intensity(sp_r * (1 - ratio), sp_g * (1 - ratio), sp_b * (1 - ratio)));
			scene.add_renderable(make_renderable_noname(new Sphere(Vector(x, y, -0.4), 0.08), 
						sp, tm));
		}
#endif


#if 1
	// floor
	scene.add_renderable(make_renderable("floor", new Sphere(Vector(0, 3.5, -10e6), 10e6-0.5), new LambertianSurfaceProperty(), new MonoTextureMapper(Intensity(0.9, 0.9, 0.9))));
	// back
	scene.add_renderable(make_renderable("back", new Sphere(Vector(0, 10e6, 0), 10e6-4.5), new LambertianSurfaceProperty(), new MonoTextureMapper(Intensity(0.9, 0.9, 0.9))));
	// left
	scene.add_renderable(make_renderable("left", new Sphere(Vector(-10e6, 3.5, 0), 10e6-1.9), new LambertianSurfaceProperty(), new MonoTextureMapper(Intensity(0.9, 0.5, 0.5))));
	// right
	scene.add_renderable(make_renderable("right", new Sphere(Vector(10e6, 3.5, 0), 10e6-1.9), new LambertianSurfaceProperty(), new MonoTextureMapper(Intensity(0.5, 0.5, 0.9))));
	// top light
	scene.add_renderable(make_renderable("top", new Sphere(Vector(0, 0, 10e6), 10e6-2.5), new MonoGlowingSurfaceProperty(Intensity(1.6, 1.47, 1.29)), new MonoTextureMapper(Intensity(0.0, 0.0, 0.0))));
	// front
	scene.add_renderable(make_renderable("front", new Sphere(Vector(0.0, -10e6, 0), 10e6-2.5), new LambertianSurfaceProperty(), new MonoTextureMapper(Intensity(1.5, 1.5, 1.5))));
#endif

	Camera camera(Vector(0, -0.5, 0), Vector(0, 1, 0), Vector(0, 0, 1),
			1.5, 2.6, 2,
			//320, 240);
			800, 600);

	RayTracer ray_tracer;
	shared_ptr<Image> image = ray_tracer.render(scene, camera);
	/*
	printf("1\n");
	Mat mat = image_to_mat(*image);
	printf("2\n");

	std::string window_name = "Hello world";
	namedWindow(window_name, CV_WINDOW_AUTOSIZE );
	imwrite("output.png", mat);
	imshow(window_name, mat);


	waitKey(0);
	*/
	return 0;
}
