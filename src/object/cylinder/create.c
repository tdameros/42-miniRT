/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 00:29:42 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/09 00:29:44 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "object.h"

t_object	cylinder_create(const t_vector3f position, const t_vector3f axis,
							const t_object_size size, const t_material material)
{
	t_object	cylinder;

	cylinder.type = CYLINDER;
	cylinder.position = position;
	cylinder.axe = axis;
	cylinder.radius = size.radius;
	cylinder.height = size.height;
	cylinder.material = material;
	cylinder.name = ft_strdup("Cylinder");

	cylinder_calculate_cache(&cylinder);
	return (cylinder);
}

void	cylinder_calculate_cache(t_object *cylinder)
{
	cylinder->cache.cone.endpoint1 = vector3f_subtract(cylinder->position,
			vector3f_multiply(cylinder->axe, cylinder->height / 2));
	cylinder->cache.cone.endpoint2 = vector3f_add(cylinder->position,
			vector3f_multiply(cylinder->axe, cylinder->height / 2));
	cylinder->cache.cylinder.cap1_normal = vector3f_multiply(cylinder->axe, -1);
	cylinder->cache.cylinder.cap2_normal = cylinder->axe;
	cylinder->cache.cylinder.cap1_d = -vector3f_dot(\
	cylinder->cache.cylinder.cap1_normal, cylinder->cache.cylinder.endpoint1);
	cylinder->cache.cylinder.cap2_d = -vector3f_dot(\
	cylinder->cache.cylinder.cap2_normal, cylinder->cache.cylinder.endpoint2);
}

t_object	cylinder_infinite_create(const t_vector3f position,
									const t_vector3f axis,
									const float radius,
									const t_material material)
{
	t_object	cylinder;

	cylinder.type = CYLINDER_INF;
	cylinder.position = position;
	cylinder.axe = axis;
	cylinder.radius = radius;
	cylinder.material = material;
	return (cylinder);
}
