/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:15:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/06/19 15:15:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPPING_H
# define MAPPING_H

# include "math/vector.h"
# include "ray_tracer/texture.h"
# include "ray_tracer/rays.h"

//	mapping.c
t_vector2f	calculate_object_map(const t_vector3f hit_position,
				const t_object *object);
t_vector2f	calculate_spherical_map(const t_vector3f hit_position,
				const t_object *sphere);
t_vector2f	calculate_cylindrical_map(const t_vector3f hit_position,
				const t_object *cylinder);
t_vector2f	calculate_planar_map(const t_vector3f hit_position,
				const t_object *plane);
t_vector2f	calculate_cap_map(const t_vector3f hit_position,
				const t_object *object);


t_vector3f	get_texture_color(t_hit hit, const t_object *object);


#endif