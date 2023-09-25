/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate_main_lines.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 03:08:59 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/24 03:09:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "threads.h"
#include "interpolater.h"

static void	interpolate_horizontal_line(t_color *pixel,
				const t_color *next_pixel);

void	*interpolate_main_lines(void *arg)
{
	t_interpolater_routines_arg	*data;
	t_color						*pixel;
	const t_color				*line_limit;
	t_color						last_calculated_pixel;

	data = get_routine_data(arg);
	mutex_lock(arg);
	while (data->next_line < data->limit)
	{
		pixel = data->next_line;
		data->next_line += data->pixels->width;
		mutex_unlock(arg);
		line_limit = pixel + data->pixels->width;
		while (pixel + data->incrementer < line_limit)
		{
			interpolate_horizontal_line(pixel, pixel + data->incrementer);
			pixel += data->incrementer;
		}
		last_calculated_pixel = *pixel;
		while (pixel < line_limit)
			*pixel++ = last_calculated_pixel;
		mutex_lock(arg);
	}
	mutex_unlock(arg);
	return (NULL);
}

static void	interpolate_horizontal_line(t_color *pixel,
				const t_color *next_pixel)
{
	const float		size = next_pixel - pixel;
	int				i;
	t_color			color;

	i = 1;
	while (i < size)
	{
		color = vector3f_multiply(*pixel, (size - i) / size);
		pixel[i] = vector3f_add(color,
				vector3f_multiply(*next_pixel, i / size));
		i++;
	}
}
