/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 01:47:37 by vfries            #+#    #+#             */
/*   Updated: 2023/09/24 03:40:30 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "colors.h"
#include "image.h"
#include "threads.h"

#define PIXEL_DIVISION 3.f

static void	*draw_circle_routine(void *routine_arg);
static void	draw_circle_pixel(unsigned int *dst, t_vector2f pixel,
				unsigned int circle_color,
				const t_draw_circle_routine_arg *circle);
static void	draw_pixel(unsigned int *dst, const unsigned int circle_color,
				const int nb_of_points_in_circle);
static bool	is_point_in_circle(t_vector2f pixel,
				const t_draw_circle_routine_arg *circle, float sub_x,
				float sub_y);

void	image_draw_circle(t_image *image, const t_vector2f circle_center,
			const float radius, const unsigned int color)
{
	t_draw_circle_routine_arg	arg;

	arg.circle_center = circle_center;
	arg.radius_squared = radius * radius;
	arg.radius = radius;
	arg.current_line = fmaxf(circle_center.y - radius - 1, 0);
	arg.max_current_line = fminf(image->height, circle_center.y + radius + 1);
	arg.x_start = fmaxf(circle_center.x - radius - 1, 0) - 1;
	arg.x_max = fminf(image->width, circle_center.x + radius + 1);
	arg.image = image;
	arg.color = color;
	start_threads(&arg, &draw_circle_routine);
}

static void	*draw_circle_routine(void *routine_arg)
{
	t_draw_circle_routine_arg	*data;
	unsigned int				x;
	unsigned int				y;
	unsigned int				*line;

	data = get_routine_data(routine_arg);
	mutex_lock(routine_arg);
	while (data->current_line < data->max_current_line)
	{
		y = data->current_line++;
		mutex_unlock(routine_arg);
		line = data->image->address + y * data->image->width;
		x = data->x_start;
		while (++x < data->x_max)
			draw_circle_pixel(line + x, (t_vector2f){x, y}, data->color, data);
		mutex_lock(routine_arg);
	}
	mutex_unlock(routine_arg);
	return (NULL);
}

static void	draw_circle_pixel(unsigned int *dst, const t_vector2f pixel,
				const unsigned int circle_color,
				const t_draw_circle_routine_arg *circle)
{
	int		sub_y;
	int		sub_x;
	int		nb_of_points_in_circle;

	nb_of_points_in_circle = 0;
	sub_y = -1;
	while (++sub_y < PIXEL_DIVISION)
	{
		sub_x = -1;
		while (++sub_x < PIXEL_DIVISION)
			nb_of_points_in_circle += is_point_in_circle(pixel, circle, sub_x,
					sub_y);
	}
	if (nb_of_points_in_circle <= 0)
		return ;
	draw_pixel(dst, circle_color, nb_of_points_in_circle);
}

static void	draw_pixel(unsigned int *dst, const unsigned int circle_color,
				const int nb_of_points_in_circle)
{
	t_color	new_color;
	int		transparency;

	new_color = vector3f_multiply(get_t_color_from_uint(circle_color),
			nb_of_points_in_circle);
	new_color = vector3f_add(new_color, vector3f_multiply(
				get_t_color_from_uint(*dst), PIXEL_DIVISION * PIXEL_DIVISION
				- nb_of_points_in_circle));
	new_color = vector3f_divide(new_color, PIXEL_DIVISION * PIXEL_DIVISION);
	transparency = (get_transparency(circle_color) * nb_of_points_in_circle
			+ get_transparency(*dst) * (PIXEL_DIVISION * PIXEL_DIVISION
				- nb_of_points_in_circle)) / (PIXEL_DIVISION * PIXEL_DIVISION);
	*dst = vec_rgb_to_uint(new_color) | (transparency << 24);
}

static bool	is_point_in_circle(const t_vector2f pixel,
				const t_draw_circle_routine_arg *circle, const float sub_x,
				const float sub_y)
{
	const float	x = pixel.x + sub_x / PIXEL_DIVISION + 1.f / PIXEL_DIVISION / 2;
	const float	y = pixel.y + sub_y / PIXEL_DIVISION + 1.f / PIXEL_DIVISION / 2;

	return (powf(x - circle->circle_center.x, 2.f)
		+ powf(y - circle->circle_center.y, 2.f) <= circle->radius_squared);
}
