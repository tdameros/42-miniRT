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
	cylinder.normal = axe;
	cylinder.radius = radius;
	cylinder.height = height;
	cylinder.material = material;
	return (cylinder);
}

