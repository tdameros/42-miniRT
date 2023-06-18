/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_infinite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:08:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/06/10 14:08:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer/rays.h"

t_object	cylinder_infinite_create(t_vector3f origin, t_vector3f axe,
									float radius, t_material material)
{
	t_object	cylinder;

	cylinder.type = CYLINDER_INF;
	cylinder.position = origin;
	cylinder.normal = axe;
	cylinder.radius = radius;
	cylinder.material = material;
	return (cylinder);
}


