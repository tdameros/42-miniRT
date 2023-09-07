/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 22:26:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/08/06 22:26:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <float.h>

#include "libft.h"

#include "math/vector.h"


static	float	calculate_triangle_area(t_vector3f vertex_a,
										   t_vector3f vertex_b,
										   t_vector3f vertex_c);

bool	point_is_in_triangle(t_vector3f point,
							t_vector3f vertex_a,
							t_vector3f vertex_b,
							t_vector3f vertex_c)
{
	const float	triangle_area = calculate_triangle_area(vertex_a, vertex_b, vertex_c);
	const float	area1 = calculate_triangle_area(vertex_a, point, vertex_b);
	const float	area2 = calculate_triangle_area(vertex_a, point, vertex_c);
	const float	area3 = calculate_triangle_area(vertex_b, point, vertex_c);

//	return (triangle_area == area1 + area2 + area3);
	return (ft_is_equalsf(triangle_area, area1 + area2 + area3, FLT_EPSILON));
}

static	float	calculate_triangle_area(t_vector3f vertex_a,
									t_vector3f vertex_b,
									t_vector3f vertex_c)
{

	return (vector3f_length(vector3f_cross(
				vector3f_subtract(vertex_b, vertex_a),
				vector3f_subtract(vertex_c, vertex_a))) / 2);
}
