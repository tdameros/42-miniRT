/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 08:47:50 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/31 08:47:53 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer/rays.h"

t_hit	calculate_ray_intersection(const t_ray *ray, const t_scene *scene)
{
	size_t		index;
	size_t		near_object_index;
	t_hit		near_hit;
	t_hit		hit;

	near_hit.distance = -1;
	index = 0;
	near_object_index = -1;
	while (index < scene->objects.length)
	{
		hit = calculate_object_distance(ray, scene->objects.data + index);
		if ((hit.distance < near_hit.distance || near_hit.distance == -1)
			&& hit.distance > 0.f)
		{
			near_hit = hit;
			near_object_index = index;
		}
		index++;
	}
	if (near_hit.distance == -1)
		return (miss_hit());
	return (hit_object(ray, scene->objects.data + near_object_index, near_hit));
}

t_hit	calculate_object_distance(const t_ray *ray, const t_object *object)
{
	if (object->type == SPHERE)
		return (calculate_sphere_distance(ray, object));
	else if (object->type == PLANE)
		return (calculate_plane_distance(ray, object));
	else if (object->type == CYLINDER_INF)
		return (calculate_inf_cylinder_distance(ray, object));
	else if (object->type == CYLINDER)
		return (calculate_cylinder_distance(ray, object));
	else if (object->type == CONE)
		return (calculate_cone_distance(ray, object));
	return (miss_hit());
}

t_hit	miss_hit(void)
{
	t_hit	hit;

	hit.hit = false;
	hit.distance = -1;
	return (hit);
}

t_hit	hit_object(const t_ray *ray, const t_object *object,
					t_hit hit_distance)
{
	if (object->type == SPHERE)
		return (hit_sphere(ray, object, hit_distance));
	else if (object->type == PLANE)
		return (hit_plane(ray, object, hit_distance));
	else if (object->type == CYLINDER_INF)
		return (hit_infinite_cylinder(ray, object, hit_distance));
	else if (object->type == CYLINDER)
		return (hit_cylinder(ray, object, hit_distance));
	else if (object->type == CONE)
		return (hit_cone(ray, object, hit_distance));
	return (miss_hit());
}
