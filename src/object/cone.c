/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 23:34:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/03 23:34:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "math/quaternion.h"

t_object	cone_create(t_vector3f origin, t_vector3f axe, float radius, float height, t_material material)
{
	t_object	cone;

	axe = quaternionf_rotate_vector3f(90, vector3f_create(0,0, 1), axe);
	axe = vector3f_unit(axe);
	cone.type = CONE;
	cone.position = origin;
	cone.axe = axe;
	cone.radius = radius;
	cone.height = height;
	cone.material = material;

	cone.cache.cone.endpoint1 = vector3f_subtract(cone.position,
			vector3f_multiply(cone.axe, cone.height / 2));
	cone.cache.cone.endpoint2 = vector3f_add(origin,
			vector3f_multiply(cone.axe, cone.height / 2));
	cone.cache.cone.radius_divide_height = (cone.radius * cone.radius)
		/ (cone.height * cone.height);
	return (cone);
}

