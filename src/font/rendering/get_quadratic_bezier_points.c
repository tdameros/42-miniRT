/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bezier_points.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 01:15:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/13 01:15:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "math/vector.h"

static void			get_lines_direction(const t_vector2f *points,
						t_vector2f *lines_direction);
static t_vector2f	get_point(const t_vector2f *points, float t,
						const t_vector2f *lines_direction);

///
/// \param points assumed to be of size 3
/// \param number_of_points
/// \return
int	get_quadratic_bezier_points(t_vector *dest, const t_vector2f *points,
		size_t number_of_points)
{
	const float	incrementer_t = 1.f / (float)number_of_points;
	float		t;
	t_vector2f	lines_direction[2];
	t_vector2f	tmp;

	get_lines_direction(points, lines_direction);
	t = 0.f;
	while (number_of_points-- && t <= 1.f)
	{
		tmp = get_point(points, t, lines_direction);
		if (ft_vector_add_elem(dest, &tmp) != VECTOR_SUCCESS)
			return (-1);
		t += incrementer_t;
	}
	return (0);
}

static void	get_lines_direction(const t_vector2f *points,
				t_vector2f *lines_direction)
{
	lines_direction[0] = vector2f_subtract(points[1], points[0]);
	lines_direction[1] = vector2f_subtract(points[2], points[1]);
}

static t_vector2f	get_point(const t_vector2f *points, const float t,
						const t_vector2f *lines_direction)
{
	const t_vector2f	line[2] = {
		vector2f_add(vector2f_multiply(lines_direction[0], t), points[0]),
		vector2f_add(vector2f_multiply(lines_direction[1], t), points[1])
	};
	const t_vector2f	line_direction = vector2f_subtract(line[1], line[0]);

	return (vector2f_add(vector2f_multiply(line_direction, t), line[0]));
}
