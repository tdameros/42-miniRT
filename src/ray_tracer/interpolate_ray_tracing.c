/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate_ray_tracing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 23:38:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/06 23:38:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	interpolate_main_lines(t_raytraced_pixels *pixels,
				int incrementer);
static void	interpolate_horizontal_line(t_raytraced_pixels *pixels, int y,
				int x, int x_end);
static void	interpolate_vertical_line(t_raytraced_pixels *pixels, int x,
				int y, int y_end);
static void	interpolate_sub_lines(t_raytraced_pixels *pixels,
				int incrementer);

void	interpolate_ray_tracing(t_raytraced_pixels *pixels,
			const int incrementer)
{
	interpolate_main_lines(pixels, incrementer);
	interpolate_sub_lines(pixels, incrementer);
}

static void	interpolate_main_lines(t_raytraced_pixels *pixels,
				const int incrementer)
{
	int		y;
	int		x;
	int		last_x;
	size_t	y_index;

	y = 0;
	while (y < pixels->height)
	{
		x = 0;
		while (x + incrementer < pixels->width)
		{
			interpolate_horizontal_line(pixels, y, x, x + incrementer);
			x += incrementer;
		}
		y_index = y * pixels->width;
		last_x = x - 1;
		while (x < pixels->width)
		{
			pixels->data[y_index + x] = pixels->data[y_index + last_x];
			x++;
		}
		y += incrementer;
	}
}

static void	interpolate_horizontal_line(t_raytraced_pixels *pixels, int y,
				const int x, const int x_end)
{
	const float		size = x_end - x;
	const size_t	line = y * pixels->width;
	int				i;
	t_color			color;

	i = 1;
	while (i < size)
	{
		color = vector3f_multiply(pixels->data[line + x], (size - i) / size);
		color = vector3f_add(color,
				vector3f_multiply(pixels->data[line + x_end], i / size));
		pixels->data[line + x + i] = color;
		i++;
	}
}

static void	interpolate_sub_lines(t_raytraced_pixels *pixels,
				const int incrementer)
{
	int			y;
	int			x;
	t_vector3f	*main_line;
	t_vector3f	*line;

	y = incrementer;
	while (y < pixels->height)
	{
		x = -1;
		while (++x < pixels->width)
			interpolate_vertical_line(pixels, x, y - incrementer, y);
		y += incrementer;
	}
	y -= incrementer;
	main_line = pixels->data + y * pixels->width;
	while (++y < pixels->height)
	{
		line = pixels->data + y * pixels->width;
		x = -1;
		while (++x < pixels->width)
			line[x] = main_line[x];
	}
}

static void	interpolate_vertical_line(t_raytraced_pixels *pixels, int x,
				const int y, const int y_end)
{
	const float		size = y_end - y;
	const t_color	y_color = pixels->data[y * pixels->width + x];
	const t_color	y_end_color = pixels->data[y_end * pixels->width + x];
	int				i;
	t_color			color;

	i = 1;
	while (i < size)
	{
		color = vector3f_multiply(y_color, (size - i) / size);
		color = vector3f_add(color, vector3f_multiply(y_end_color, i / size));
		pixels->data[(y + i) * pixels->width + x] = color;
		i++;
	}
}
