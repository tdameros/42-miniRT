/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 08:50:59 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/31 08:51:01 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADE_H
# define SHADE_H

# include "scene.h"
# include "ray_tracer/rays.h"

//	light.c
t_vector3f	calculate_light_contribution(const t_scene *scene, \
									const t_light light, \
									const t_hit object_hit);

//	shade.c
t_vector3f	calculate_shade(const t_scene *scene, const t_hit object_hit, \
							const float intensity);

//	shadow.c
bool		is_shadow_pixel(const t_scene *scene, const t_light light,
				const t_hit object_hit, t_vector3f reverse_light_direction);

#endif
