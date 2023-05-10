#include "vector.h"
#include <stdio.h>
#include <math.h>

// (bx^2 + by^2)t^2 + (2(axbx + ayby))t + (ax^2 + ay^2 - r^2) = 0
// a = ray origin
// b = ray direction
// r = radius
// t = hit distance
//t_vector3	render_pixel(t_vector3 ray_origin, t_vector3 ray_direction)
//{
//	double radius = 0.5;
//
//	double a = vector3_dot(ray_direction, ray_direction);
//	double b = 2 * vector3_dot(ray_origin, ray_direction);
//	double c = vector3_dot(ray_origin, ray_origin) - radius * radius;
//
//	double discriminant = b * b - 4 * a * c;
//	if (discriminant > 0)
//	{
////		double x1 = (-b + sqrt(discriminant)) / (2 * a);
//		double x2 = (-b - sqrt(discriminant)) / (2 * a);
//
//		if (x2 < 0)
//			return (vector3_create(0.27, 0.27, 0.27));
//		t_vector3 hit = vector3_add(ray_origin,
//									vector3_multiply(ray_direction, x2));
////		t_vector3 normal = vector3_add(vector3_multiply(vector3_unit(hit), 0.5),
////									   vector3_create(0.5, 0.5, 0.5));
////		t_vector3 normal = vector3_unit(hit);
//		t_vector3 normal = hit;
//
////		t_vector3 light_direction = vector3_unit(vector3_create(1, -1, -1));
//		t_vector3 light_direction = vector3_create(1, -1, -1);
//
//		double light_intensity = vector3_dot(normal,
//											 vector3_multiply(light_direction,
//															  -1));
//		if (light_intensity < 0)
//			light_intensity = 0;
////		light_intensity += light;
////		if (light_intensity > 1)
////			light_intensity = 1;
//		t_vector3 sphere_color = vector3_create(0.26, 0.75, 0.98);
//		return (vector3_multiply(sphere_color, light_intensity));
//	}
//	return (vector3_create(0.27, 0.27, 0.27));
//}

#include "ray.h"
#include "scene.h"
#include "object.h"
#include "struct/t_color.h"
#include "hit.h"

t_hit		trace_ray(t_ray ray, t_scene *scene);
t_hit		calculate_hit(t_ray ray, t_scene *scene, double distance, size_t index);
t_vector3	miss_hit(t_ray ray);

t_color	render_pixel(t_ray ray, t_scene *scene)
{
	t_hit			ray_hit;
	const t_vector3	light_direction = vector3_create(1, -1, -1);
	double			light_intensity;
	t_object		sphere;

	ray_hit = trace_ray(ray, scene);
	if (!ray_hit.hit)
		return (miss_hit(ray));
	light_intensity = vector3_dot(ray_hit.normal,
			vector3_multiply(light_direction, -1));
	sphere = scene->objects.data[ray_hit.object_index];
	return (vector3_multiply(sphere.albedo, light_intensity));
}

t_hit	trace_ray(t_ray ray, t_scene *scene)
{
	ssize_t		near_object_index;
	size_t		index;
	double		near_distance;
	double		distance;

	near_object_index = -1;
	near_distance = -1;
	index = 0;
	while (index < scene->objects.length)
	{
		distance = hit_sphere(ray, scene->objects.data[index]);
		if ((distance < near_distance || near_object_index == -1)
			&& distance > 0)
		{
			near_distance = distance;
			near_object_index = index;
		}
		index++;
	}
	if (near_distance == -1)
		return ((t_hit){false, 0, 0, (t_vector3) {0, 0, 0}, (t_vector3) {0, 0, 0}});
	return (calculate_hit(ray, scene, near_distance, near_object_index));
}

t_hit	calculate_hit(t_ray ray, t_scene *scene, double distance, size_t index)
{
	t_object	sphere;
	t_vector3	origin;
	t_vector3	direction;
	t_vector3	hit;

	sphere = scene->objects.data[index];
	origin = vector3_subtract(ray.origin, sphere.position);
	direction = vector3_multiply(ray.direction, distance);
	hit = vector3_add(origin, direction);
	return ((t_hit){true, distance, index, hit, hit});
}

t_vector3	miss_hit(t_ray ray)
{
	(void ) ray;
	return (vector3_create(0.27, 0.27, 0.27));
}