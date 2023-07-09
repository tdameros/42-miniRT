/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 23:28:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/02 23:28:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "ray_tracer/rays.h"
#include "ray_tracer/shade.h"
#include "math/vector.h"


t_vector3f	calculate_shade(const t_scene *scene, const t_hit object_hit,
							const float intensity)
{
	t_vector3f	shade_albedo;
	t_vector3f	light_contribution;
	size_t		i;

	shade_albedo = vector3f_mult_vector3f(scene->ambient_light.emitted_color,
			object_hit.albedo);
	i = 0;
	while (i < scene->lights.length)
	{
		light_contribution = calculate_light_contribution(scene, \
														scene->lights.data[i], \
														object_hit);
		shade_albedo = vector3f_add(shade_albedo, light_contribution);
		i++;
	}
	return (vector3f_multiply(shade_albedo, intensity));
}