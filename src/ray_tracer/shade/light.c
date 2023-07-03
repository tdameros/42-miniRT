/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 23:27:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/02 23:27:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "light.h"
#include "scene.h"
#include "ray_tracer/shade.h"
#include "ray_tracer/rays.h"

static t_vector3f	calculate_diffuse_light(const t_light light,
						const t_vector3f reverse_light_direction,
						const t_hit object_hit);

static t_vector3f	calculate_specular_light(const t_light light,
						const t_vector3f light_direction,
						const t_hit ray_hit);

t_vector3f	calculate_light_contribution(const t_scene *scene,
										const t_light light,
										const t_hit object_hit)
{
	t_vector3f	reverse_light_direction;
	t_vector3f	light_direction;
	t_vector3f	color;

	reverse_light_direction = vector3f_subtract(light.position, \
												object_hit.position);
	reverse_light_direction = vector3f_unit(reverse_light_direction);
	if (is_shadow_pixel(scene, object_hit, reverse_light_direction))
		return (vector3f_create(0, 0, 0));
	light_direction = vector3f_subtract(object_hit.position, light.position);
	light_direction = vector3f_unit(light_direction);
	color = calculate_diffuse_light(light, reverse_light_direction, object_hit);
	color = vector3f_add(color, calculate_specular_light(light, light_direction,
				object_hit));
	return (color);
}

static t_vector3f	calculate_diffuse_light(const t_light light,
									const t_vector3f reverse_light_direction,
									const t_hit object_hit)
{
	const float			scalar_product = ft_maxf(0,
			vector3f_dot(object_hit.normal, reverse_light_direction));
	const t_vector3f	emitted_light = calculate_emitted_light(light);

	return (vector3f_multiply(vector3f_mult_vector3f(object_hit.albedo,
				emitted_light), scalar_product));
}

static t_vector3f	calculate_specular_light(const t_light light,
											const t_vector3f light_direction,
											const t_hit ray_hit)
{
	const t_vector3f	reflect_ray = vector3f_unit(reflect(light_direction,
				ray_hit.normal));
	const t_vector3f	emitted_light = calculate_emitted_light(light);
	float				scalar_product;

	scalar_product = ft_maxf(0, vector3f_dot(reflect_ray,
				vector3f_unit(vector3f_multiply(ray_hit.ray.direction, -1))));
	scalar_product = powf(scalar_product, 100);
	return (vector3f_multiply(vector3f_mult_vector3f(ray_hit.albedo,
				emitted_light), scalar_product));
}

t_vector3f	calculate_ambient_light(const t_light ambient_light,
									const t_hit object_hit)
{
	return (vector3f_mult_vector3f(object_hit.albedo,
			calculate_emitted_light(ambient_light)));
}

t_vector3f	calculate_emitted_light(const t_light light)
{
	return (vector3f_multiply(light.color, light.brightness));
}
