/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 00:28:33 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/09 00:28:36 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "object.h"

t_object	cone_create(const t_vector3f position, const t_vector3f axis,
						const t_object_size size,
						const t_material material)
{
	t_object	cone;

	cone.type = CONE;
	cone.position = position;
	cone.axe = axis;
	cone.radius = size.radius;
	cone.height = size.height;
	cone.material = material;
	cone.name = ft_strdup("Cone");

	cone_calculate_cache(&cone);
	return (cone);
}

void	cone_calculate_cache(t_object *cone)
{
	cone->cache.cone.endpoint1 = vector3f_subtract(cone->position,
			vector3f_multiply(cone->axe, cone->height / 2));
	cone->cache.cone.endpoint2 = vector3f_add(cone->position,
			vector3f_multiply(cone->axe, cone->height / 2));
	cone->cache.cone.radius_divide_height = (cone->radius * cone->radius)
		/ (cone->height * cone->height);
	cone->cache.cone.cap_normal = vector3f_multiply(cone->axe, -1);
	cone->cache.cone.cap_d = -vector3f_dot(cone->cache.cone.cap_normal,
			cone->cache.cone.endpoint1);
}

