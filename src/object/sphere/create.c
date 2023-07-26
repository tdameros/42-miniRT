/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 01:20:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/09 01:20:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "object.h"

t_object	sphere_create(const t_vector3f position, const float radius,
						const t_material material)
{
	t_object	sphere;

	sphere.type = SPHERE;
	sphere.position = position;
	sphere.radius = radius;
	sphere.material = material;
	sphere.name = ft_strdup("Sphere");

	sphere_calculate_cache(&sphere);
	return (sphere);
}

void	sphere_calculate_cache(t_object *sphere)
{
	sphere->cache.sphere.square_radius = sphere->radius * sphere->radius;
}
