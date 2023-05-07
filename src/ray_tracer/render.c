#include "vector.h"
#include <stdio.h>
#include <math.h>

// (bx^2 + by^2)t^2 + (2(axbx + ayby))t + (ax^2 + ay^2 - r^2) = 0
// a = ray origin
// b = ray direction
// r = radius
// t = hit distance
t_vector3	render_pixel(t_vector3 ray_origin, t_vector3 ray_direction)
{
	double radius = 0.5;

	double a = vector3_dot(ray_direction, ray_direction);
	double b = 2 * vector3_dot(ray_origin, ray_direction);
	double c = vector3_dot(ray_origin, ray_origin) - radius * radius;

	double discriminant = b * b - 4 * a * c;
	if (discriminant > 0)
	{
//		double x1 = (-b + sqrt(discriminant)) / (2 * a);
		double x2 = (-b - sqrt(discriminant)) / (2 * a);

		if (x2 < 0)
			return (vector3_create(0.27, 0.27, 0.27));
		t_vector3 hit = vector3_add(ray_origin,
									vector3_multiply(ray_direction, x2));
//		t_vector3 normal = vector3_add(vector3_multiply(vector3_unit(hit), 0.5),
//									   vector3_create(0.5, 0.5, 0.5));
//		t_vector3 normal = vector3_unit(hit);
		t_vector3 normal = hit;

//		t_vector3 light_direction = vector3_unit(vector3_create(1, -1, -1));
		t_vector3 light_direction = vector3_create(1, -1, -1);

		double light_intensity = vector3_dot(normal,
											 vector3_multiply(light_direction,
															  -1));
		if (light_intensity < 0)
			light_intensity = 0;
//		light_intensity += light;
//		if (light_intensity > 1)
//			light_intensity = 1;
		t_vector3 sphere_color = vector3_create(0.26, 0.75, 0.98);
		return (vector3_multiply(sphere_color, light_intensity));
	}
	return (vector3_create(0.27, 0.27, 0.27));
}

#include "ray.h"
#include "scene.h"
#include "object.h"

//t_color	render_pixel(t_ray ray, t_scene *scene)
//{
//	t_sphere	*sphere;
//	t_sphere	*near_sphere;
//	t_list		*spheres;
//	double		hit_scalar;
//	double		best_scalar;
//
//	near_sphere = NULL;
//	spheres = scene->spheres;
//	while (spheres != NULL)
//	{
//		sphere = spheres->content;
//		if (hit_sphere(ray, *sphere))
//		{
//			hit_scalar = get_hit_scalar_sphere(ray, *sphere);
//			if (hit_scalar > 0 && (near_sphere == NULL || hit_scalar < best_scalar))
//			{
//				best_scalar = hit_scalar;
//				near_sphere = sphere;
//			}
//		}
//		spheres = spheres->next;
//	}
//	if (near_sphere == NULL)
//		return (vector3_create(0.27, 0.27, 0.27));
//	t_vector3 hit = vector3_add(vector3_subtract(ray.origin, sphere->origin),
//									vector3_multiply(ray.direction, best_scalar));
//	t_vector3 normal = vector3_unit(hit);
//	t_vector3 light_direction = vector3_create(1, -1, -1);
//	double light_intensity = vector3_dot(normal,
//											 vector3_multiply(light_direction,
//															  -1));
//	if (light_intensity < 0)
//		light_intensity = 0;
//	t_vector3 sphere_color = vector3_create(0.26, 0.75, 0.98);
//	return (vector3_multiply(sphere_color, light_intensity));
//}
