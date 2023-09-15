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

#include "image.h"
#include "threads.h"
#include "colors.h"

static void	*round_image_corners_routine(void *routine_arg);

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
		{
			if (is_in_top_left_corner(x, y, data->radius)
				|| is_in_top_right_corner(x, y, data->radius, data->image)
				|| is_in_bottom_left_corner(x, y, data->radius, data->image)
				|| is_in_bottom_right_corner(x, y, data->radius, data->image))
				line[x] = COLOR_TRANSPARENT;
		}
		mutex_lock(routine_arg);
	}
	mutex_unlock(routine_arg);
	return (NULL);
}
