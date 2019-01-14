#include <iostream>
#include "ray.h"

vec3 color(const ray &r)
{
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5 * (unit_direction.y() + 1.0);
	return (1 - t) * vec3(0.0, 0.0, 0.0) + t * vec3(0.5, 0.0, 0.0);
}

int main()
{
	int nx = 2000;
	int ny = 1000;

	std::cout << "P3\n"
						<< nx << " " << ny << "\n255\n";
	vec3 lower_left(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(origin, lower_left + u * horizontal + v * vertical);
			vec3 col = color(r);
			int ir = int(col.r() * 255.99);
			int ig = int(col.g() * 255.99);
			int ib = int(col.b() * 255.99);
			std::cout << ir << " " << ig << " " << ib << std::endl;
		}
	}
}