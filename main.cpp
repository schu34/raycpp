#include <iostream>
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"
#include <random>

vec3 color(const ray &r, hitable *world)
{
  hit_record rec;
  if (world->hit(r, 0.0, MAXFLOAT, rec))
  {
    return 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
  }
  else
  {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
  }
}

int main()
{
  int nx = 2000;
  int ny = 1000;
  int ns = 1000;

  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  hitable *list[2];
  list[0] = new sphere(vec3(0, 0, -1), 0.5);
  list[1] = new sphere(vec3(0, -100.5, -1), 100);

  hitable *world = new hitable_list(list, 2);
  camera cam;

  for (int j = ny - 1; j >= 0; j--)
  {
    for (int i = 0; i < nx; i++)
    {
      vec3 col(0,0,0);
      for(int s=0; s< ns; s++){
        float u = float(i + drand48()) / float(nx);
        float v = float(j + drand48()) / float(ny);
        ray r = cam.get_ray(u, v);
        col += color(r, world);
      }
      col /= ns;
      int ir = int(col.r() * 255.99);
      int ig = int(col.g() * 255.99);
      int ib = int(col.b() * 255.99);
      std::cout << ir << " " << ig << " " << ib << std::endl;
    }
  }
}