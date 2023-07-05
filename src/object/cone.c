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

t_object	cone_create(t_vector3f origin, t_vector3f axe, float radius, float height, t_material material)
{
	t_object	cone;

	cone.type = CONE;
	cone.position = origin;
	cone.normal = axe;
	cone.radius = radius;
	cone.height = height;
	cone.material = material;
	return (cone);
}
