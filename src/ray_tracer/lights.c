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

#include "math/vector.h"
#include "scene.h"
#include "ray_tracer/hit.h"

t_vector3f	calculate_color(t_scene *scene, t_hit ray_hit)
{
	t_vector3f	light_direction;
	float		light_intensity;
//	t_color		color;

	light_direction = vector3f_unit(vector3f_subtract(scene->light.position, ray_hit.position));
	light_intensity = vector3f_dot(ray_hit.normal, light_direction);
	if (light_intensity < 0)
		light_intensity = 0;
//	color = vector3f_divide(ray_hit.object.albedo, 255);
//	color = mult
	return (light_direction);
}

float	calculate_light_intensity(t_scene *scene, t_hit ray_hit)
{
//	t_hit			light_hit;
//	t_ray			light_ray;
	t_vector3f		light_direction;
	float 			light_intensity;

	light_direction = vector3f_unit(vector3f_subtract(ray_hit.position, scene->light.position));
//	light_ray = ray_create(vector3f_add(ray_hit.position, vector3f_multiply(ray_hit.normal, 0.001f)),
//						   vector3f_multiply(light_direction, -1));
//	light_hit = calculate_ray_intersection(light_ray, scene);
//	if (light_hit.hit)
//		return (0.1f);
//		color = vector3f_multiply(color, 0.1f);
	light_intensity = vector3f_dot(ray_hit.normal,
								   vector3f_multiply(light_direction, -1));
	if (light_intensity < 0)
		light_intensity = 0;
	if (light_intensity >= 1)
		light_intensity = 1;
	return (light_intensity);
}
