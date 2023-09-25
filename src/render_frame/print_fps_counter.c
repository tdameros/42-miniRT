/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fps_counter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:48:54 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/24 00:48:55 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "mlx.h"

#include "engine.h"

static bool	should_update_fps(struct timeval last_update);

void	print_fps_counter(t_engine *engine, const struct timeval start_time)
{
	if (should_update_fps(engine->gui.fps.last_update))
	{
		free(engine->gui.fps.fps_count);
		engine->gui.fps.fps_nb = ft_get_number_of_fps(start_time);
		engine->gui.fps.fps_count = ft_itoa(engine->gui.fps.fps_nb);
		if (engine->gui.fps.fps_count == NULL)
		{
			ft_putstr_fd("Error: Failed to malloc minirt->gui.fps.fps_count\n",
				STDERR_FILENO);
			close_engine(engine);
		}
		engine->gui.fps.last_update = ft_get_current_time();
	}
	if (engine->gui.fps.fps_count)
		mlx_string_put(engine->window.mlx, engine->window.window, 40, 40,
			0xFF0000, engine->gui.fps.fps_count);
	else
		mlx_string_put(engine->window.mlx, engine->window.window, 40, 40,
			0xFF0000, "Failed to get fps count");
}

inline static bool	should_update_fps(const struct timeval last_update)
{
	const struct timeval	current_time = ft_get_current_time();

	return (current_time.tv_sec * NB_OF_USECONDS_IN_A_SECOND
		+ current_time.tv_usec
		- last_update.tv_sec * NB_OF_USECONDS_IN_A_SECOND - last_update.tv_usec
		> 200 * NB_OF_USECONDS_IN_A_MILLISECOND);
}
