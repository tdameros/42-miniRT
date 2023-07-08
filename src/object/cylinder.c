/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:16:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/31 13:16:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

t_object	cylinder_create(t_vector3f origin, t_vector3f axe, float radius, float height, t_material material)
{
	t_object	cylinder;

	cylinder.type = CYLINDER;
	cylinder.position = origin;
	cylinder.axe = axe;
	cylinder.radius = radius;
	cylinder.height = height;
	cylinder.material = material;

	cylinder.cache.cone.endpoint1 = vector3f_subtract(cylinder.position,
			vector3f_multiply(cylinder.axe, cylinder.height / 2));
	cylinder.cache.cone.endpoint2 = vector3f_add(origin,
			vector3f_multiply(cylinder.axe, cylinder.height / 2));

	cylinder.cache.cylinder.cap1_normal = vector3f_multiply(cylinder.axe, -1);
	cylinder.cache.cylinder.cap2_normal = cylinder.axe;
	cylinder.cache.cylinder.cap1_d = -vector3f_dot(\
	cylinder.cache.cylinder.cap1_normal, cylinder.cache.cylinder.endpoint1);
	cylinder.cache.cylinder.cap2_d = -vector3f_dot(\
	cylinder.cache.cylinder.cap2_normal, cylinder.cache.cylinder.endpoint2);
	return (cylinder);
}

