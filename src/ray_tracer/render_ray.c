/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 02:04:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/08 02:04:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "math/vector.h"
#include "ray_tracer/rays.h"
#include "ray_tracer/shade.h"

t_vector3f	render_ray(t_ray ray, const t_scene *scene)
{
	t_hit			ray_hit;
	t_vector3f		ray_color;
	t_vector3f		color;
	const int		bounces_per_pixel = 5;
	float			multiplier;

	multiplier = 1.0f;
	ray_color = vector3f_create(0, 0, 0);
	for (int i = 0; i < bounces_per_pixel; i++)
	{
		if (multiplier < 0.01f)
			return (ray_color);
		ray_hit = calculate_ray_intersection(&ray, scene);
		if (!ray_hit.hit)
		{
			color = vector3f_multiply(scene->sky_color, multiplier);
			ray_color = vector3f_add(ray_color, color);
			return (ray_color);
		}

		color = calculate_shade(scene, ray_hit, multiplier);
		ray_color = vector3f_add(ray_color, color);
		multiplier *= ray_hit.object->material.reflect;
		ray.origin = vector3f_add(ray_hit.position,
				vector3f_multiply(ray_hit.normal, 0.01f));
		ray.direction = reflect(ray.direction, ray_hit.normal);
	}
	return (ray_color);
}

t_vector3f	render_ray_icon(t_ray ray, const t_scene *scene, int *missed_object)
{
	t_hit			ray_hit;
	t_vector3f		ray_color;
	t_vector3f		color;
	const int		bounces_per_pixel = 5;
	float			multiplier;

	multiplier = 1.0f;
	ray_color = vector3f_create(0, 0, 0);
	for (int i = 0; i < bounces_per_pixel; i++)
	{
		if (multiplier < 0.01)
			return (ray_color);
		ray_hit = calculate_ray_intersection(&ray, scene);
		if (!ray_hit.hit)
		{
			color = vector3f_multiply(scene->sky_color, multiplier);
			ray_color = vector3f_add(ray_color, color);
			if (i == 0)
				(*missed_object)++;
			return (ray_color);
		}

		// Lights
//		color = calculate_color(scene, ray_hit, multiplier);
		color = calculate_shade(scene, ray_hit, multiplier);
		ray_color = vector3f_add(ray_color, color);
		multiplier *= ray_hit.object->material.reflect;
		ray.origin = vector3f_add(ray_hit.position,
				vector3f_multiply(ray_hit.normal, 0.01f));
		ray.direction = reflect(ray.direction, ray_hit.normal);
	}
	return (ray_color);
}
