/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 10:05:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/17 10:05:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "engine.h"
#include "colors.h"

static void	put_pixel(t_image *image, t_vector2i point,
				t_vector3f color);
static void	put_line_dx_greater(t_image *image,
				t_vector2i point1, t_vector2i point2, t_vector3f color);
static void	put_line_dy_greater(t_image *image,
				t_vector2i point1, t_vector2i point2, t_vector3f color);

void	draw_line(t_image *image,
				t_vector2i point1, t_vector2i point2,
				t_vector3f color)
{
	double	dx;
	double	dy;

	if (point1.x < 0 || point2.x < 0)
		return ;
	dx = fabs((double) point2.x - point1.x);
	dy = fabs((double) point2.y - point1.y);
	if (dx >= dy)
		put_line_dx_greater(image, point1, point2, color);
	else
		put_line_dy_greater(image, point1, point2, color);
}

static void	put_line_dx_greater(t_image *image,
								t_vector2i point1, t_vector2i point2,
								t_vector3f color)
{
	const double	dx = fabs((double) point2.x - point1.x);
	const double	dy = fabs((double) point2.y - point1.y);
	const double	m = dy / dx;
	double			e;
	int				i;

	i = 0;
	e = 0;
	while (i++ <= dx)
	{
		put_pixel(image, point1, color);
		if (point1.x > point2.x)
			point1.x--;
		else
			point1.x++;
		e -= m;
		if (e <= -0.5)
		{
			if (point1.y > point2.y)
				point1.y--;
			else
				point1.y++;
			e += 1;
		}
	}
}

static void	put_line_dy_greater(t_image *image,
								t_vector2i point1, t_vector2i point2,
								t_vector3f color)
{
	const double	dx = fabs((double) point2.x - point1.x);
	const double	dy = fabs((double) point2.y - point1.y);
	const double	m = dx / dy;
	double			e;
	int				i;

	i = 0;
	e = 0;
	while (i++ <= dy)
	{
		put_pixel(image, point1, color);
		if (point1.y > point2.y)
			point1.y--;
		else
			point1.y++;
		e -= m;
		if (e <= -0.5)
		{
			if (point1.x > point2.x)
				point1.x--;
			else
				point1.x++;
			e += 1;
		}
	}
}

static void	put_pixel(t_image *image, t_vector2i point,
					t_vector3f color)
{
	unsigned int	int_color;

	if (point.x <= 0 || point.x >= image->width)
		return ;
	if (point.y <= 0 || point.y >= image->height)
		return ;
	int_color = vec_rgb_to_uint(color);
	image->address[point.x + point.y * image->width] = int_color;
}
