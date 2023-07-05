/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:11:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/03 18:11:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "ray_tracer/rays.h"
#include "math/equation.h"

t_hit	hit_cone(const t_ray *ray, const t_object *cone, const float distance)
{
	t_hit	hit;

	hit.distance = distance;
	if (hit.distance < 0)
	{
		hit.hit = false;
		return (hit);
	}
	hit.hit = true;
	hit.position = ray_at(ray, distance);
	hit.normal = cone->normal;
	hit.normal = vector3f_create(0, 0, 0);
//	if (vector3f_dot(hit.normal, ray->direction) > 0)
//		hit.normal = vector3f_multiply(hit.normal, -1);
	hit.object = cone;
	hit.ray = *ray;
//	if (hit.object->material.is_checked_pattern)
//		hit.albedo = get_checked_pattern(hit, cone);
//	else
	hit.albedo = cone->material.albedo;
	return (hit);

}

#include <stdio.h>
float	calculate_cone_distance(const t_ray *ray, const t_object *cone)
{
	float	equation[3];
	float	result[2];

	t_vector3f	v = vector3f_unit(ray->direction);
	t_vector3f	s  = vector3f_unit(cone->normal);
	t_vector3f ra0 = vector3f_cross(s, vector3f_subtract(ray->origin, cone->position));
	ra0 = vector3f_cross(ra0, s);
//	vector3f_print(ra0);
	t_vector3f	va = vector3f_cross(s, v);
	va = vector3f_cross(va, s);
//	vector3f_print(va);
//	float h = vector3f_dot(vector3f_subtract(ray->direction, cone->position), s);
	float H = cone->height;
	float h0 = vector3f_dot(vector3f_subtract(ray->origin, cone->position), s);
//	printf("h0: %f\n", h0);
	float vs = vector3f_dot(v, s);
//	printf("vs: %f\n", vs);
	float W = H - h0;
	float R = cone->radius;

	float r_divde_h = (R * R) / (H * H);
	float a = vector3f_dot(va, va);
//	printf("A: %f\n", a);
	a = a - (vs * vs) * r_divde_h;

	float b = vector3f_dot(vector3f_multiply(ra0, 2), va);
//	float b = vector3f_dot(ra0, va) * 2;
	b += 2 * W * vs * r_divde_h;

	float c = vector3f_dot(ra0, ra0);
	c = c - (W * W) * r_divde_h;

//	printf("A: %f B: %f C: %f\n", a, b, c);
	equation[0] = a;
	equation[1] = b;
	equation[2] = c;
	if (!solve_quadratic_equation(equation[0], equation[1], equation[2], result))
		return (-1);
	return (ft_minf_positive(result[0], result[1]));
}
