/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 23:27:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/02 23:27:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "ray_tracer/rays.h"

static t_hit	calculate_shadow_ray_intersection(const t_scene *scene, \
												const t_ray *ray);

bool	is_shadow_pixel(const t_scene *scene, const t_hit object_hit,
						const t_vector3f reverse_light_direction)
{
	const t_vector3f	new_position = vector3f_add(object_hit.position, \
								vector3f_multiply(object_hit.normal, 0.001f));
	const t_ray			light_ray = ray_create(new_position, \
								reverse_light_direction);
	const t_hit			light_hit = calculate_shadow_ray_intersection(\
								scene, &light_ray);
	float				light_distance;
	float				hit_distance;

	if (!object_hit.hit)
		return (false);
	light_distance = vector3f_length(vector3f_subtract(scene->light.position,
				object_hit.position));
	hit_distance = vector3f_length(vector3f_subtract(light_hit.position,
				object_hit.position));
	return (light_hit.hit && hit_distance < light_distance);
}

static t_hit	calculate_shadow_ray_intersection(const t_scene *scene, \
												const t_ray *ray)

{
	size_t		index;
	float		distance;

	index = 0;
	while (index < scene->objects.length)
	{
		distance = calculate_object_distance(ray, scene->objects.data + index);
		if (distance > 0)
			return (hit_object(ray, scene->objects.data + index, distance));
		index++;
	}
	return (miss_hit());
}

