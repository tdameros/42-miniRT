/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 00:38:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/09 00:38:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

t_object	plane_create(const t_vector3f position, const t_vector3f normal,
						const t_material material)
{
	t_object	plane;

	plane.type = PLANE;
	plane.position = position;
	plane.axe = normal;
	plane.material = material;

	plane_calculate_cache(&plane);
	return (plane);
}

void	plane_calculate_cache(t_object *plane)
{
	plane->cache.plane.d = -vector3f_dot(plane->axe, plane->position);
}
