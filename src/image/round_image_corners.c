/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_image_corners.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:39:06 by vfries            #+#    #+#             */
/*   Updated: 2023/07/30 18:39:24 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "libft.h"

#include "image.h"
#include "threads.h"
#include "colors.h"

#define PIXEL_DIVISION 3.f

static void	*round_image_corners_routine(void *routine_arg);
static void	write_pixel(t_round_image_corners_routine_arg *data, int x, int y,
				unsigned int *line);

void	round_image_corners(t_image *image, int radius)
{
	const int							max_radius = fmin(
			image->height, image->width) / 2;
	t_round_image_corners_routine_arg	arg;

	arg.current_line = 0;
	arg.radius = fmax(0, fmin(radius, max_radius));
	arg.image = image;
	start_threads(&arg, &round_image_corners_routine);
}

static void	*round_image_corners_routine(void *routine_arg)
{
	t_round_image_corners_routine_arg	*data;
	int									y;
	int									x;
	unsigned int						*line;

	data = get_routine_data(routine_arg);
	mutex_lock(routine_arg);
	while (data->current_line < data->image->height)
	{
		y = data->current_line++;
		mutex_unlock(routine_arg);
		line = data->image->address + y * data->image->width;
		x = data->image->width;
		while (x--)
			write_pixel(data, x, y, line + x);
		mutex_lock(routine_arg);
	}
	mutex_unlock(routine_arg);
	return (NULL);
}

static void	write_pixel(t_round_image_corners_routine_arg *data, int x, int y,
				unsigned int *dst)
{
	int		sub_y;
	int		sub_x;
	int		nb_of_points_in_corner;
	int16_t	transparency;

	nb_of_points_in_corner = 0;
	sub_y = -1;
	while (++sub_y < PIXEL_DIVISION)
	{
		sub_x = -1;
		while (++sub_x < PIXEL_DIVISION)
			nb_of_points_in_corner += is_point_in_corner(
					x + sub_x / PIXEL_DIVISION + 1.f / PIXEL_DIVISION / 2,
					y + sub_y / PIXEL_DIVISION + 1.f / PIXEL_DIVISION / 2,
					data->radius, data->image);
	}
	if (nb_of_points_in_corner <= 0)
		return ;
	transparency = get_transparency(*dst)
		+ nb_of_points_in_corner / (PIXEL_DIVISION * PIXEL_DIVISION) * 255.f;
	transparency = ft_clamp(transparency, 0, 255);
	*dst = (*dst & 0x00FFFFFF) | (transparency << 24);
}
