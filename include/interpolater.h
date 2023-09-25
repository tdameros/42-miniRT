/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolater.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 03:35:43 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/25 03:35:44 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPOLATER_H
# define INTERPOLATER_H

# include "engine.h"

typedef struct s_interpolater_routines_arg
{
	t_color						*next_line;
	const t_color				*limit;
	const t_raytraced_pixels	*pixels;
	int							incrementer;
	bool						first_thread_finished;
}	t_interpolater_routines_arg;

void	interpolate_ray_tracing(t_raytraced_pixels *pixels,
			int incrementer);
void	*interpolate_main_lines(void *arg);
void	*interpolate_sub_lines(void *arg);

#endif
