/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 03:06:12 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/24 03:06:13 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

#include "engine.h"

#ifdef __APPLE__

int	mouse_move(t_engine *engine, t_vector2i position)
{
	if (engine->window.is_focused == false)
		return (0);
	engine->mouse_position = position;
	return (mlx_mouse_move(engine->window.window, position.x, position.y));
}
#endif
#ifdef __linux__

int	mouse_move(t_engine *engine, t_vector2i position)
{
	if (engine->window.is_focused == false)
		return (0);
	engine->mouse_position = position;
	return (mlx_mouse_move(engine->window.mlx, engine->window.window,
			position.x, position.y));
}
#endif
