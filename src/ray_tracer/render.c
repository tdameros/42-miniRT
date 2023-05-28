#include "math/vector.h"
#include "ray_tracer/ray.h"
#include "scene.h"
#include "object.h"
#include "ray_tracer/hit.h"

t_hit		trace_ray(t_ray ray, t_scene *scene);
t_hit		calculate_hit(t_ray ray, t_scene *scene, double distance, size_t index);
t_vector3f	miss_hit(t_ray ray);

int bouncesPerPixel = 2;

t_vector3f	reflect(t_vector3f i, t_vector3f n)
{
	return(vector3f_subtract(i,vector3f_multiply(n, vector3f_dot(n, i) * 2.0f)));
}

t_color	render_pixel(t_ray ray, t_scene *scene)
{
	t_hit			ray_hit;
	t_hit 			light_hit;
	t_ray			light_ray;
	t_vector3f		light_direction;
	float			light_intensity;
	t_object		object;
	t_vector3f		result = vector3f_create(0, 0, 0); // Set ambiant light here
	float 			multiplier = 1.0f;
	t_vector3f 		color;

	for (int i = 0; i < bouncesPerPixel; i++)
	{
		ray_hit = trace_ray(ray, scene);
		if (!ray_hit.hit)
		{
			t_vector3f sky = vector3f_create(0.0f, 0.0f, 0.0f);
			result = vector3f_add(result, vector3f_multiply(sky, multiplier));
			return (result);
		}
		object = scene->objects.data[ray_hit.object_index];

		// Lights
		light_direction = vector3f_unit(vector3f_subtract(ray_hit.position, scene->light.position));
		light_ray = ray_create(vector3f_add(ray_hit.position, vector3f_multiply(ray_hit.normal, 0.001f)),
							   vector3f_multiply(light_direction, -1));
		light_hit = trace_ray(light_ray, scene);
		if (light_hit.hit && i == 0)
			return (vector3f_multiply(object.albedo, 0.1f));
		light_intensity = vector3f_dot(ray_hit.normal,
									   vector3f_multiply(light_direction, -1));
		if (light_intensity < 0)
			light_intensity = 0;
		light_intensity *= multiplier;

		// Color
		color = vector3f_multiply(object.albedo, light_intensity);
		result = vector3f_add(result, color);
		multiplier *= 0.1f;
		ray.origin = vector3f_add(ray_hit.position, vector3f_multiply(ray_hit.normal, 0.0001f));
		ray.direction = reflect(ray.direction, ray_hit.normal);
	}
	return (result);
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
		distance = hit_object(ray, scene->objects.data[index]);
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

t_hit	calculate_hit(t_ray ray, t_scene *scene, double distance, size_t index)
{
	t_object	sphere;
	t_vector3f	origin;
	t_vector3f	direction;
	t_vector3f	hit_position;
	t_vector3f	hit_normal;

	sphere = scene->objects.data[index];
	origin = vector3f_subtract(ray.origin, sphere.position);
	direction = vector3f_multiply(ray.direction, distance);
	hit_position = vector3f_add(origin, direction);
	if (sphere.type == PLANE)
		hit_normal = vector3f_unit(sphere.normal);
	else
		hit_normal = vector3f_unit(hit_position);
	hit_position = vector3f_add(hit_position, sphere.position);
	return ((t_hit){true, distance, index, hit_position, hit_normal});
}

t_vector3f	miss_hit(t_ray ray)
{
	(void ) ray;
//	return (vector3f_create(0.2, 0.2, 0.8));
	return (vector3f_create(0, 0, 0));
}