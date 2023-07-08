/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:43:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/07 15:43:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

t_object	sphere_create(t_vector3f origin, float radius, t_material material)
{
	t_object	sphere;

	sphere.type = SPHERE;
	sphere.position = origin;
	sphere.radius = radius;
	sphere.material = material;

	sphere.cache.sphere.square_radius = sphere.radius * sphere.radius;
	return (sphere);
}

