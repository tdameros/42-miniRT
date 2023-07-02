/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:33:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/19 23:33:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "math/vector.h"
#include "scene.h"
#include "ray_tracer/rays.h"

static bool	is_shadow(const t_scene *scene, t_hit ray_hit,
						 t_vector3f reverse_light_direction);
static t_vector3f	apply_light_brightness(const t_light *light);
static t_vector3f	calculate_ambient_light(const t_scene *scene, t_hit ray_hit);
static t_vector3f	calculate_diffuse_light(const t_scene *scene,
											 t_hit ray_hit, t_vector3f reverse_light_direction);
static t_vector3f	calculate_specular_light(const t_scene *scene,
											  t_hit ray_hit,
											  t_vector3f light_direction);

t_vector3f	calculate_color(const t_scene *scene, t_hit ray_hit, float multiplier)
{
	t_vector3f	reverse_light_direction;
	t_color		ambient;
	t_color		diffuse;
	t_color		specular;
//	t_color		color;

//	reverse_light_direction = vector3f_subtract(ray_hit.position, scene->light.position);
	ambient = calculate_ambient_light(scene, ray_hit);
	ambient = vector3f_multiply(ambient, multiplier);
	reverse_light_direction = vector3f_subtract(scene->light.position, ray_hit.position);
	reverse_light_direction = vector3f_unit(reverse_light_direction);
	if (is_shadow(scene, ray_hit, reverse_light_direction))
		return (ambient);
	diffuse = calculate_diffuse_light(scene, ray_hit, reverse_light_direction);
	diffuse = vector3f_multiply(diffuse, multiplier);
	specular = calculate_specular_light(scene, ray_hit, vector3f_multiply(reverse_light_direction, -1));
	specular = vector3f_multiply(specular, multiplier);
	specular = vector3f_multiply(specular, ray_hit.object->material.specular);
	return (vector3f_add(vector3f_add(diffuse, ambient), specular));
}

static bool	is_shadow(const t_scene *scene, t_hit ray_hit,
		t_vector3f reverse_light_direction)
{
	const t_vector3f	new_position = vector3f_add(ray_hit.position,
			vector3f_multiply(ray_hit.normal, 0.001f));
	const t_ray			light_ray = ray_create(new_position,
			reverse_light_direction);
	const t_hit			light_hit = calculate_ray_intersection(&light_ray,
			scene);
	float				light_distance;
	float				hit_distance;

	if (!ray_hit.hit)
		return (false);
	light_distance = vector3f_length(vector3f_subtract(scene->light.position,
				ray_hit.position));
	hit_distance = vector3f_length(vector3f_subtract(light_hit.position,
				ray_hit.position));
	return (light_hit.hit && hit_distance < light_distance);
}

static t_vector3f	apply_light_brightness(const t_light *light)
{
	return (vector3f_multiply(light->color, light->brightness));
}

static t_vector3f	calculate_ambient_light(const t_scene *scene, t_hit ray_hit)
{
	const t_vector3f	ambient_light_color = apply_light_brightness(\
		&scene->ambient_light);
	const float			red = ray_hit.albedo.x * ambient_light_color.x;
	const float			green = ray_hit.albedo.y
		* ambient_light_color.y;
	const float			blue = ray_hit.albedo.z * ambient_light_color.z;

	return (vector3f_create(red, green, blue));
}


static t_vector3f	calculate_diffuse_light(const t_scene *scene,
											t_hit ray_hit,
											t_vector3f reverse_light_direction)
{
	const float			scalar_product = ft_maxf(0, vector3f_dot(ray_hit.normal,
				reverse_light_direction));
	const t_vector3f	light_color = apply_light_brightness(\
		&scene->light);
	const float			red = ray_hit.albedo.x * light_color.x
		* scalar_product;
	const float			green = ray_hit.albedo.y * light_color.y
		* scalar_product;
	const float			blue = ray_hit.albedo.z * light_color.z
		* scalar_product;

	return (vector3f_create(red, green, blue));
}

static t_vector3f	calculate_specular_light(const t_scene *scene,
											  t_hit ray_hit,
											  t_vector3f light_direction)
{
	const t_vector3f	reflect_ray = vector3f_unit(reflect(light_direction, ray_hit.normal));
	float			scalar_product = ft_maxf(0, vector3f_dot(reflect_ray,
	vector3f_unit(vector3f_multiply(ray_hit.ray.direction, -1))));
	scalar_product = powf(scalar_product, 100);
	const t_vector3f	light_color = apply_light_brightness(\
		&scene->light);
	const float			red = ray_hit.albedo.x * light_color.x
		* scalar_product;
	const float			green = ray_hit.albedo.y * light_color.y
		* scalar_product;
	const float			blue = ray_hit.albedo.z * light_color.z
		* scalar_product;

	return (vector3f_create(red, green, blue));
}