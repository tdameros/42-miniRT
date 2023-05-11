#include <stdio.h>
#include <math.h>

#include "math/vector.h"

// (bx^2 + by^2)t^2 + (2(axbx + ayby))t + (ax^2 + ay^2 - r^2) = 0
// a = ray origin
// b = ray direction
// r = radius
// t = hit distance
//t_vector3f	render_pixel(t_vector3f ray_origin, t_vector3f ray_direction)
//{
//	float radius = 0.5;
//
//	float a = vector3f_dot(ray_direction, ray_direction);
//	float b = 2 * vector3f_dot(ray_origin, ray_direction);
//	float c = vector3f_dot(ray_origin, ray_origin) - radius * radius;
//
//	float discriminant = b * b - 4 * a * c;
//	if (discriminant > 0)
//	{
////		float x1 = (-b + sqrtf(discriminant)) / (2 * a);
//		float x2 = (-b - sqrtf(discriminant)) / (2 * a);
//
//		if (x2 < 0)
//			return (vector3f_create(0.27, 0.27, 0.27));
//		t_vector3f hit = vector3f_add(ray_origin,
//									vector3f_multiply(ray_direction, x2));
////		t_vector3f normal = vector3f_add(vector3f_multiply(vector3f_unit(hit), 0.5),
////									   vector3f_create(0.5, 0.5, 0.5));
////		t_vector3f normal = vector3f_unit(hit);
//		t_vector3f normal = hit;
//
////		t_vector3f light_direction = vector3f_unit(vector3f_create(1, -1, -1));
//		t_vector3f light_direction = vector3f_create(1, -1, -1);
//
//		float light_intensity = vector3f_dot(normal,
//											 vector3f_multiply(light_direction,
//															  -1));
//		if (light_intensity < 0)
//			light_intensity = 0;
////		light_intensity += light;
////		if (light_intensity > 1)
////			light_intensity = 1;
//		t_vector3f sphere_color = vector3f_create(0.26, 0.75, 0.98);
//		return (vector3f_multiply(sphere_color, light_intensity));
//	}
//	return (vector3f_create(0.27, 0.27, 0.27));
//}

#include "ray_tracer/ray.h"
#include "scene.h"
#include "object.h"
#include "colors.h"
#include "ray_tracer/hit.h"

t_hit		trace_ray(t_ray ray, t_scene *scene);
t_hit		calculate_hit(t_ray ray, t_scene *scene, float distance, size_t index);
t_vector3f	miss_hit(t_ray ray);

t_color	render_pixel(t_ray ray, t_scene *scene)
{
	t_hit			ray_hit;
	const t_vector3f	light_direction = vector3f_create(1, -1, -1);
	float			light_intensity;
	t_object		sphere;

	ray_hit = trace_ray(ray, scene);
	if (!ray_hit.hit)
		return (miss_hit(ray));
	light_intensity = vector3f_dot(ray_hit.normal,
								   vector3f_multiply(light_direction, -1));
	sphere = scene->objects.data[ray_hit.object_index];
	return (vector3f_multiply(sphere.albedo, light_intensity));
}

t_hit	trace_ray(t_ray ray, t_scene *scene)
{
	ssize_t		near_object_index;
	size_t		index;
	float		near_distance;
	float		distance;

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
		return ((t_hit){false, 0, 0, (t_vector3f) {0, 0, 0}, (t_vector3f) {0, 0, 0}});
	return (calculate_hit(ray, scene, near_distance, near_object_index));
}

t_hit	calculate_hit(t_ray ray, t_scene *scene, float distance, size_t index)
{
	t_object	sphere;
	t_vector3f	origin;
	t_vector3f	direction;
	t_vector3f	hit;

	sphere = scene->objects.data[index];
	origin = vector3f_subtract(ray.origin, sphere.position);
	direction = vector3f_multiply(ray.direction, distance);
	hit = vector3f_add(origin, direction);
	return ((t_hit){true, distance, index, hit, hit});
}

t_vector3f	miss_hit(t_ray ray)
{
	(void ) ray;
	return (vector3f_create(0.27, 0.27, 0.27));
}