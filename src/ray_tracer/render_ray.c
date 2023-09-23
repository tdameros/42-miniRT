/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:01:56 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/31 09:01:59 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "math/vector.h"
#include "ray_tracer/rays.h"
#include "ray_tracer/shade.h"
#include "ray_tracer/render.h"

#define ICON_BOUNCES_PER_PIXEL 2

static	t_ray	calculate_bounce_ray(t_ray current_ray, t_hit ray_hit);

t_vector3f	render_ray(t_ray ray, const t_scene *scene)
{
	t_hit			ray_hit;
	t_vector3f		ray_color;
	t_vector3f		color;
	float			multiplier;
	unsigned int	i;

	i = 0;
	multiplier = 1.0f;
	ray_color = vector3f_create(0, 0, 0);
	while (i < scene->bounces_per_pixel)
	{
		if (multiplier < 0.01f)
			return (ray_color);
		ray_hit = calculate_ray_intersection(&ray, scene);
		if (!ray_hit.hit)
			return (vector3f_add(ray_color, \
					vector3f_multiply(scene->sky_color, multiplier)));
		color = calculate_shade(scene, ray_hit, multiplier);
		ray_color = vector3f_add(ray_color, color);
		multiplier *= ray_hit.object->material.reflection;
		ray = calculate_bounce_ray(ray, ray_hit);
		i++;
	}
	return (ray_color);
}

static	t_ray	calculate_bounce_ray(t_ray current_ray, t_hit ray_hit)
{
	t_ray	new_ray;

	new_ray.origin = vector3f_add(ray_hit.position,
			vector3f_multiply(ray_hit.normal, 0.01f));
	new_ray.direction = reflect(current_ray.direction, ray_hit.normal);
	return (new_ray);
}

t_vector3f	render_ray_icon(t_ray ray, const t_scene *scene, int *missed_object)
{
	t_hit			ray_hit;
	t_vector3f		ray_color;
	t_vector3f		color;
	float			multiplier;
	unsigned int	i;

	i = -1;
	multiplier = 1.0f;
	ray_color = vector3f_create(0, 0, 0);
	while (++i < ICON_BOUNCES_PER_PIXEL)
	{
		if (multiplier < 0.01f)
			return (ray_color);
		ray_hit = calculate_ray_intersection(&ray, scene);
		if (!ray_hit.hit)
		{
			*missed_object += i == 0;
			return (vector3f_add(ray_color, \
					vector3f_multiply(scene->sky_color, multiplier)));
		}
		color = calculate_shade(scene, ray_hit, multiplier);
		ray_color = vector3f_add(ray_color, color);
		multiplier *= ray_hit.object->material.reflection;
		ray = calculate_bounce_ray(ray, ray_hit);
	}
	return (ray_color);
}
