/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:20:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/15 17:20:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "math/vector.h"
#include "ray_tracer/rays.h"

t_object	plane_create(t_vector3f position, t_vector3f normal,
						t_material material)
{
	t_object	plane;

	plane.type = PLANE;
	plane.position = position;
	plane.normal = normal;
	plane.material = material;
	return (plane);
}


