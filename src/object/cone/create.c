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

static void	calculate_bounding_box_face(t_vector3f *face, t_vector3f center,
										   t_vector3f circle_vector1,
										   t_vector3f circle_vector2);

t_object	cone_create(const t_vector3f position, const t_vector3f axis,
						const t_object_size size,
						const t_material material)
{
	t_object	cone;

	ft_bzero(&cone, sizeof(cone));
	cone.type = CONE;
	cone.position = position;
	cone.axis = axis;
	cone.radius = size.radius;
	cone.height = size.height;
	cone.material = material;
	cone.name = ft_strdup("Cone");
	cone_calculate_cache(&cone);
	cone_calculate_bounding_box(&cone);
	return (cone);
}

void	cone_calculate_cache(t_object *cone)
{
	cone->cache.cone.endpoint1 = vector3f_subtract(cone->position,
			vector3f_multiply(cone->axis, cone->height / 2));
	cone->cache.cone.endpoint2 = vector3f_add(cone->position,
			vector3f_multiply(cone->axis, cone->height / 2));
	cone->cache.cone.radius_divide_height = (cone->radius * cone->radius)
		/ (cone->height * cone->height);
	cone->cache.cone.cap_normal = vector3f_multiply(cone->axis, -1);
	cone->cache.cone.cap_d = -vector3f_dot(cone->cache.cone.cap_normal,
			cone->cache.cone.endpoint1);
}

void	cone_calculate_bounding_box(t_object *cone)
{
	t_vector3f	center_bottom;
	t_vector3f	center_top;
	t_vector3f	circle_vector1;
	t_vector3f	circle_vector2;

	center_bottom = vector3f_add(cone->position,
								 vector3f_multiply(cone->axis, cone->height / 2));
	center_top = vector3f_subtract(cone->position,
								   vector3f_multiply(cone->axis, cone->height / 2));
	circle_vector1 = vector3f_cross(cone->axis,
									(t_vector3f){0.f, 1.f, 0.f});
	if (vector3f_length(circle_vector1) == 0)
		circle_vector1 = vector3f_cross(cone->axis,
										(t_vector3f){1.f, 0.f, 0.f});
	circle_vector1 = vector3f_unit(circle_vector1);
	circle_vector2 = vector3f_unit(vector3f_cross(circle_vector1,
												  cone->axis));
	circle_vector1 = vector3f_multiply(circle_vector1, cone->radius);
	circle_vector2 = vector3f_multiply(circle_vector2, cone->radius);
	calculate_bounding_box_face(cone->bounding_box.top_face, center_top, \
								circle_vector1, circle_vector2);
	calculate_bounding_box_face(cone->bounding_box.bottom_face, \
								center_bottom, \
								circle_vector1, circle_vector2);
	object_calculate_aabb_min_max(cone);
}

static void	calculate_bounding_box_face(t_vector3f *face, t_vector3f center,
										   t_vector3f circle_vector1,
										   t_vector3f circle_vector2)
{
	face[0] = vector3f_add(center,
						   vector3f_add(circle_vector1, circle_vector2));
	face[1] = vector3f_add(center,
						   vector3f_subtract(circle_vector2, circle_vector1));
	face[2] = vector3f_subtract(center,
								vector3f_add(circle_vector1, circle_vector2));
	face[3] = vector3f_add(center,
						   vector3f_subtract(circle_vector1, circle_vector2));
}
