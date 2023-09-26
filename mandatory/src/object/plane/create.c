/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 00:38:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/26 16:04:05 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "object.h"

t_object	plane_create(const t_vector3f position,
				const t_vector3f rotation_degrees,
				const t_material material)
{
	t_object	plane;

	ft_bzero(&plane, sizeof(plane));
	plane.type = PLANE;
	plane.position = position;
	plane.axis_degrees = (t_vector3f){0};
	plane.axis = vector3f_unit(rotation_degrees);
	plane.material = material;
	plane.name = ft_strdup("Plane");
	plane_calculate_cache(&plane);
	return (plane);
}

void	plane_calculate_cache(t_object *plane)
{
	plane->cache.plane.d = -vector3f_dot(plane->axis, plane->position);
}
