/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:17:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/18 17:17:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include "float.h"

#include "ray_tracer/rays.h"
#include "ray_tracer/bvh.h"

bool	ray_intersect_aabb(const t_ray *ray, const t_vector3f aabb_min,
						const t_vector3f aabb_max, float near_distance)
{
	float	tmin;
	float	tmax;
	int		axis_index;
	float	inverse_direction;
	float	t[2];

	tmin = -FLT_MAX;
	tmax = FLT_MAX;
	axis_index = 0;
	while (axis_index < 3)
	{
		inverse_direction = 1.0f / vector3f_get(ray->direction, axis_index);
		t[0] = (vector3f_get(aabb_min, axis_index)
				- vector3f_get(ray->origin, axis_index)) * inverse_direction;
		t[1] = (vector3f_get(aabb_max, axis_index)
				- vector3f_get(ray->origin, axis_index)) * inverse_direction;
		if (inverse_direction < 0.0f)
			ft_swap_float(&t[0], &t[1]);
		tmin = fmaxf(t[0], tmin);
		tmax = fminf(t[1], tmax);
		if (tmax <= tmin)
			return (false);
		axis_index++;
	}
	return (tmin < near_distance);
}
