#include<iostream>
#include"Common_Constants.h"
#include"color.h"
#include"Hittable_list.h"
#include"Sphere.h"
#include"Camera.h"
Color ray_color(const Ray& r, const Hittable& world,int depth) {
	if (depth < 0)
		return Color(0, 0, 0);
	Hit_Record rec;
	if (world.hit(r, infinity, 0.001, rec)) 
	{
		Vec3 target = rec.normal + random_unit_vector();
		return 0.1*ray_color(Ray(rec.p, target), world,depth-1);
	}
	Vec3 unit_direction = dot_product(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}
int main() {
	Hittable_List world;
	world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
	world.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));
	
	//image 
	const int image_width = 256;
	const int image_height = image_width;
	const int samples_per_pixel = 100;
	const int max_depth = 50;

	//camera
	Camera cam;
	std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
	//display image
	for (int j = image_height - 1; j >= 0; j--) {
		std::cerr << "Lines remaining " << j << '\n';
		for (int i = 0; i < image_width; i++) {
			Color pixel_color(0, 0, 0);
			for (int k = 0; k < samples_per_pixel; k++) {
				auto u = double(i+random_double()) / (image_width - 1);
				auto v = double(j+ random_double()) / (image_height - 1);
				pixel_color += ray_color(cam.get_ray(u, v), world,max_depth);
			}
			write_color(std::cout, pixel_color,samples_per_pixel);
		}
	}
	std::cerr << "Render finished!"<<std::flush;
	return 0;
}