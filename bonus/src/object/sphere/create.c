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

	ft_bzero(&sphere, sizeof(sphere));
	sphere.type = SPHERE;
	sphere.position = position;
	sphere.radius = radius;
	sphere.material = material;
	sphere.name = ft_strdup("Sphere");
	sphere_calculate_cache(&sphere);
	sphere_calculate_bounding_box(&sphere);
	return (sphere);
}

void	sphere_calculate_cache(t_object *sphere)
{
	sphere->cache.sphere.square_radius = sphere->radius * sphere->radius;
}

void	sphere_calculate_bounding_box(t_object *sphere)
{
	sphere->bounding_box.top_face[0] = vector3f_add(sphere->position,
			(t_vector3f){sphere->radius, sphere->radius, -sphere->radius});
	sphere->bounding_box.top_face[1] = vector3f_add(sphere->position,
			(t_vector3f){sphere->radius, sphere->radius, sphere->radius});
	sphere->bounding_box.top_face[2] = vector3f_add(sphere->position,
			(t_vector3f){-sphere->radius, sphere->radius, sphere->radius});
	sphere->bounding_box.top_face[3] = vector3f_add(sphere->position,
			(t_vector3f){-sphere->radius, sphere->radius, -sphere->radius});
	sphere->bounding_box.bottom_face[0] = vector3f_add(sphere->position,
			(t_vector3f){sphere->radius, -sphere->radius, -sphere->radius});
	sphere->bounding_box.bottom_face[1] = vector3f_add(sphere->position,
			(t_vector3f){sphere->radius, -sphere->radius, sphere->radius});
	sphere->bounding_box.bottom_face[2] = vector3f_add(sphere->position,
			(t_vector3f){-sphere->radius, -sphere->radius, sphere->radius});
	sphere->bounding_box.bottom_face[3] = vector3f_add(sphere->position,
			(t_vector3f){-sphere->radius, -sphere->radius, -sphere->radius});
	object_calculate_aabb_min_max(sphere);
}
