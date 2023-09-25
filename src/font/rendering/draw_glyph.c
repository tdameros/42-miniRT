/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_glyph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 14:36:00 by vfries            #+#    #+#             */
/*   Updated: 2023/09/24 01:43:46 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "font/render.h"
#include "threads.h"

// PIXEL_DIVISION should be >= 1 (1 means no anti aliasing)
#define PIXEL_DIVISION 3.f

static void						*draw_glyph_routine(void *arg_void);
static t_glyph_generated_points	get_adjusted_points(
									const t_glyph_generated_points *raw_points,
									float scale, float x_offset,
									float y_offset);
static void						draw_pixel(unsigned int *dst,
									t_vector2f pixel,
									t_vector3f background_color,
									const t_glyph_generated_points *points);

typedef struct s_draw_glyph_routine_arg
{
	t_glyph_generated_points	points;
	int							current_line;
	t_color						color;
	t_image						*image;
}	t_draw_glyph_routine_arg;

void	draw_glyph(const t_glyph_generated_points *raw_points,
			t_draw_glyph_data data)
{
	t_draw_glyph_routine_arg	arg;

	arg.points = get_adjusted_points(raw_points, data.scale, data.x_offset,
			data.y_offset);
	if (arg.points.points == NULL)
		return ;
	arg.current_line = arg.points.bounds.y_min * data.scale;
	arg.color = get_t_color_from_uint(data.color);
	arg.image = data.image;
	start_threads(&arg, &draw_glyph_routine);
	free(arg.points.points);
}

static void	*draw_glyph_routine(void *arg_void)
{
	t_draw_glyph_routine_arg		*data;
	int								x;
	int								y;
	unsigned int					*dst;

	data = get_routine_data(arg_void);
	mutex_lock(arg_void);
	while (data->current_line <= data->points.bounds.y_max)
	{
		y = data->current_line++;
		mutex_unlock(arg_void);
		x = data->points.bounds.x_min - 1;
		while (++x <= data->points.bounds.x_max)
		{
			dst = data->image->address + y * data->image->width + x;
			if (dst < data->image->address)
				continue ;
			if (dst >= data->image->limit)
				return (NULL);
			draw_pixel(dst, (t_vector2f){x, y}, data->color, &data->points);
		}
		mutex_lock(arg_void);
	}
	mutex_unlock(arg_void);
	return (NULL);
}

static t_glyph_generated_points	get_adjusted_points(
									const t_glyph_generated_points *raw_points,
									const float scale, const float x_offset,
									const float y_offset)
{
	t_glyph_generated_points	result;
	size_t						i;

	result.points = malloc(sizeof(*result.points) * raw_points->nb_of_points);
	if (result.points == NULL)
	{
		ft_print_error("Failed to draw glyph, allocation failed\n");
		return (result);
	}
	i = raw_points->nb_of_points;
	while (i--)
	{
		result.points[i] = vector2f_multiply(raw_points->points[i], scale);
		result.points[i].x += x_offset;
		result.points[i].y += y_offset;
	}
	result.nb_of_points = raw_points->nb_of_points;
	result.bounds = (t_glyph_outline_bounds){
		.x_min = raw_points->bounds.x_min * scale + x_offset,
		.x_max = raw_points->bounds.x_max * scale + x_offset + 1,
		.y_min = raw_points->bounds.y_min * scale + y_offset,
		.y_max = raw_points->bounds.y_max * scale + y_offset + 1};
	result.nb_of_contours = raw_points->nb_of_contours;
	result.contours_limits = raw_points->contours_limits;
	return (result);
}

static void	draw_pixel(unsigned int *dst, const t_vector2f pixel,
				const t_vector3f background_color,
				const t_glyph_generated_points *points)
{
	int		sub_y;
	int		sub_x;
	int		nb_of_points_in_glyph;
	t_color	new_color;

	nb_of_points_in_glyph = 0;
	sub_y = -1;
	while (++sub_y < PIXEL_DIVISION)
	{
		sub_x = -1;
		while (++sub_x < PIXEL_DIVISION)
			nb_of_points_in_glyph += is_point_inside_glyph(\
				(t_vector2f){pixel.x + sub_x / PIXEL_DIVISION + 1.f \
				/ PIXEL_DIVISION / 2, pixel.y + sub_y / PIXEL_DIVISION + 1.f \
				/ PIXEL_DIVISION / 2}, points);
	}
	if (nb_of_points_in_glyph <= 0)
		return ;
	new_color = vector3f_multiply(background_color,
			nb_of_points_in_glyph);
	new_color = vector3f_add(new_color, vector3f_multiply(
				get_t_color_from_uint(*dst), PIXEL_DIVISION * PIXEL_DIVISION
				- nb_of_points_in_glyph));
	new_color = vector3f_divide(new_color, PIXEL_DIVISION * PIXEL_DIVISION);
	*dst = vec_rgb_to_uint(new_color);
}
