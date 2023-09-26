/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 08:53:10 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/31 08:53:22 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "math/vector.h"
# include "ray_tracer/texture.h"
# include "ray_tracer/rays.h"

//	mapping.c
t_vector2f	calculate_object_map(const t_vector3f hit_position,
				const t_object *object);
t_vector2f	calculate_cap_map(const t_vector3f hit_position,
				const t_object *object);

//	normal.c
t_vector3f	calculate_normal_perturbation(t_hit hit, const t_object *object);

//	textures.c
t_vector3f	get_texture_color(t_hit hit, const t_object *object);

#endif
