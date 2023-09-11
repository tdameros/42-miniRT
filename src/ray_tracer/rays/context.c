/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:43:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/11 16:43:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "ray_tracer/rays.h"

bool	is_cap_context(enum e_hit_context context)
{
	return (context == CAP1 || context == CAP2);
}

bool	context_has_normal_map(enum e_hit_context context,
							const t_material *material)
{
	return ((context == OUTLINE && material->textures.outline.has_normals_map)
		|| (is_cap_context(context) && material->textures.cap.has_normals_map));
}
