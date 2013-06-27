
#include <iostream>
#include <string>

#include "common.hh"
#include "util.hh"

int main( int argc, char** argv )
{
	Scene scene;

	//{{{ scene: simple caustic and strong noise
#if 0
#if 0
	scene.add_renderable(make_renderable("back", new Sphere(Vector(50,40.8, 1e5),1e5),
				new LambertianSurfaceProperty(), new MonoTextureMapper(Intensity(.75,.75,.75))));
	scene.add_renderable(make_renderable("front", new Sphere(Vector(50,40.8, -1e5+170),1e5),
				new LambertianSurfaceProperty(), new MonoTextureMapper(Intensity(0, 0, 0))));
#endif

	//scene.add_renderable(make_renderable("right", new Sphere(Vector(1e5+99,40.8,81.6),1e5), new LambertianSurfaceProperty(), new MonoTextureMapper(Intensity(.7,.7,.9))));

	scene.add_renderable(make_renderable("left", new Sphere(Vector(-1e5+1,40.8,81.6), 1e5), 
				new LambertianSurfaceProperty(), new MonoTextureMapper(Intensity(0.5, 0.9, 0.5))));

	scene.add_renderable(make_renderable("bottom", new Sphere(Vector(50,-1e5, 81.6),1e5),
				new LambertianSurfaceProperty(), new MonoTextureMapper(Intensity(0.9, 0.9, 0.9))));

	scene.add_renderable(make_renderable("front", new Sphere(Vector(50, 40.8, -1e5-170), 1e5), new GlassSurfaceProperty(0.05), new MonoTextureMapper(Intensity(0.9, 1.0, 0.9))));

	real_t light_radius = 16;
	scene.add_renderable(make_renderable("light", new Sphere(Vector(20,10+81.6-.27 + light_radius, 81.6), light_radius),
				new MonoGlowingSurfaceProperty(Intensity(10, 10, 10)), new MonoTextureMapper(Intensity(0, 0, 0)),
				new Material(1.5)));

	scene.add_renderable(make_renderable("light-right", new Sphere(Vector(20+100,10+81.6-.27 + light_radius, 81.6), light_radius),
				new MonoGlowingSurfaceProperty(Intensity(10, 10, 10)), new MonoTextureMapper(Intensity(0, 0, 0)),
				new Material(1.5)));

	scene.add_renderable(make_renderable("mirror", new Sphere(Vector(27,16.5,47), 16.5),
				new ChromeSurfaceProperty(), new MonoTextureMapper(Intensity(1, 1, 1))));
	scene.add_renderable(make_renderable("glass", new Sphere(Vector(73,16.5,78), 16.5), new GlassSurfaceProperty(0), new MonoTextureMapper(Intensity(0.999,0.999,0.999)), new Material(1.5)));

#if 0
	Mesh *tetrahedron = new Mesh();
	{
		real_t s3 = sqrt(3.0);
		tetrahedron->v = {Vector(0, 0, 2), Vector(s3, 0, -1), Vector(-s3, 0, -1), Vector(0, s3, 0)};
		tetrahedron->face = {Mesh::Face({0, 1, 3}), Mesh::Face({1, 2, 3}), Mesh::Face({2, 0, 3}), Mesh::Face({2, 1, 0})};
		tetrahedron->normalize().scale(10).translate(30, 16.6, 100);
	}
	tetrahedron->finish();
	scene.add_renderable(make_renderable("tetrahedron", tetrahedron, new LambertianSurfaceProperty(), new MonoTextureMapper(Intensity(0.4, 0.4, 0.95))));
#endif


	//scene.add_renderable(make_renderable("light", new Sphere(Vector(50,681.6-.27, 81.6), 600), new MonoGlowingSurfaceProperty(Intensity(1.2, 1.2, 1.2)), new MonoTextureMapper(Intensity(0, 0, 0)), new Material(1.5))); 
	Camera camera(Vector(50, 52, 295.6), Vector(0, -0.042612, -1), Vector(0, 1, 0),
			5,
			4, 3,
			//320, 240);
		   800, 600);

#endif
	//}}}

	//{{{ scene: dragon in box
#if 1
	/*{{{ balls*/
	scene.add_renderable(make_renderable("glowing ball", new Sphere(Vector(0, 2.8, 0), 0.3), new MonoGlowingSurfaceProperty(Intensity(10.6, 10.47, 10.29)), new MonoTextureMapper(Intensity(1.0, 1.0, 1.0))));
	scene.add_renderable(make_renderable("glass ball", new Sphere(Vector(1.1, 2.6, 0), 0.5), new GlassSurfaceProperty(-1), new MonoTextureMapper(Intensity(0.8, 1.0, 0.7)), new Material(1.5)));
	scene.add_renderable(make_renderable("chrome ball", new Sphere(Vector(-1.1, 2.8, 0), 0.5), new ChromeSurfaceProperty(), new MonoTextureMapper(Intensity(0.8, 0.8, 0.8))));
	/*}}}*/

	Mesh *humanoid_tri = mesh_read_from_file("resources/obj/dragon/dragon-0.50.obj");
	humanoid_tri->normalize().scale(0.4).rotate_deg(0, 90).translate(-0.1, 1.4, 0.0);
	humanoid_tri->finish();
	scene.add_renderable(make_renderable("humanoid_tri", humanoid_tri, new GlassSurfaceProperty(), new MonoTextureMapper(Intensity(0.75, 0.75, 0.95)), new Material(1.5)));

	/*{{{ walls*/
	scene.add_renderable(make_renderable("floor", new Sphere(Vector(0, 3.5, -10e6), 10e6-0.5), new LambertianSurfaceProperty(), new MonoTextureMapper(Intensity(0.9, 0.9, 0.9))));
	scene.add_renderable(make_renderable("back", new Sphere(Vector(0, 10e6, 0), 10e6-4.5), new LambertianSurfaceProperty(), new MonoTextureMapper(Intensity(0.9, 0.9, 0.9))));
	scene.add_renderable(make_renderable("left", new Sphere(Vector(-10e6, 3.5, 0), 10e6-1.9), new LambertianSurfaceProperty(), new MonoTextureMapper(Intensity(0.9, 0.5, 0.5))));
	scene.add_renderable(make_renderable("right", new Sphere(Vector(10e6, 3.5, 0), 10e6-1.9), new LambertianSurfaceProperty(), new MonoTextureMapper(Intensity(0.5, 0.5, 0.9))));
	scene.add_renderable(make_renderable("top", new Sphere(Vector(0, 0, 10e6), 10e6-2.5), new MonoGlowingLambertianSurfaceProperty(Intensity(1.6, 1.47, 1.29)), new MonoTextureMapper(Intensity(0.0, 0.0, 0.0))));
	scene.add_renderable(make_renderable("front", new Sphere(Vector(0.0, -10e6, 0), 10e6-2.5), new LambertianSurfaceProperty(), new MonoTextureMapper(Intensity(1.5, 1.5, 1.5))));
	/*}}}*/
	Camera camera(Vector(0, -0.8, 0), Vector(0, 1, 0), Vector(0, 0, 1),
			1.2, 2.6, 1.4625,
			//200, 122);
		   //400, 225);
		   800, 450);
	//1920, 1080);
#endif
	// }}}

	RayTracer ray_tracer;
	for (int i = 0; i < 360; i ++) {
		printf("Frame: %d\n", i); fflush(stdout);
		humanoid_tri->normalize().scale(0.4).rotate_deg(2, 1).translate(-0.1, 1.4, 0.0);
		humanoid_tri->finish();
		Image *image = ray_tracer.render(scene, camera);
		if (image)
			delete image;
	}

	return 0;
}

/**
 * vim: syntax=cpp11 foldmethod=marker
 */

