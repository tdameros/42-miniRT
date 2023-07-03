/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:35:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/20 17:35:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer/rays.h"


t_hit	calculate_ray_intersection(const t_ray *ray, const t_scene *scene)
{
	size_t		index;
	size_t		near_object_index;
	float		near_distance;
	float		distance;

	near_distance = -1;
	index = 0;
	near_object_index = -1;
	while (index < scene->objects.length)
	{
		distance = calculate_object_distance(ray, scene->objects.data + index);
		if ((distance < near_distance || near_distance == -1)
			&& distance > 0)
		{
			near_distance = distance;
			near_object_index = index;
		}
		index++;
	}
	if (near_distance == -1)
		return (miss_hit());
	return (hit_object(ray, scene->objects.data + near_object_index, near_distance));
}

t_hit	miss_hit(void)
{
	t_hit	hit;

	hit.hit = false;
	return (hit);
}

float	calculate_object_distance(const t_ray *ray, const t_object *object)
{
	if (object->type == SPHERE)
		return (calculate_sphere_distance(ray, object));
	else if (object->type == PLANE)
		return (calculate_plane_distance(ray, object));
	else if (object->type == CYLINDER_INF)
		return (calculate_inf_cylinder_distance(ray, object));
	else if (object->type == CYLINDER)
		return (calculate_cylinder_distance(ray, object));
	return (-1);
}

t_hit	hit_object(const t_ray *ray, const t_object *object, float distance)
{
	if (object->type == SPHERE)
		return (hit_sphere(ray, object, distance));
	else if (object->type == PLANE)
		return (hit_plane(ray, object, distance));
	else if (object->type == CYLINDER_INF)
		return (hit_infinite_cylinder(ray, object, distance));
	else if (object->type == CYLINDER)
		return (hit_cylinder(ray, object, distance));
	return (miss_hit());
}