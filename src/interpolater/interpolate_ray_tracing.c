/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate_ray_tracing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 23:38:00 by vfries            #+#    #+#             */
/*   Updated: 2023/09/20 18:15:34 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "threads.h"
#include "interpolater.h"

void	interpolate_ray_tracing(t_raytraced_pixels *pixels,
			const int incrementer)
{
	t_interpolater_routines_arg	arg;

	arg.next_line = pixels->data;
	arg.limit = pixels->data + pixels->width * pixels->height;
	arg.pixels = pixels;
	arg.incrementer = incrementer;
	start_threads(&arg, &interpolate_main_lines);
	arg.first_thread_finished = false;
	arg.next_line = pixels->data;
	start_threads(&arg, &interpolate_sub_lines);
}
