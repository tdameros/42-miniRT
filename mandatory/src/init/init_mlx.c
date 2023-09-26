/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:07:08 by vfries            #+#    #+#             */
/*   Updated: 2023/09/25 17:02:41 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

#include "engine.h"
#include "events.h"
#include "render_frame.h"
#include "hooks.h"
#include "mlx_wrapper.h"

static void	init_hooks(t_engine *engine);

int	init_mlx(t_engine *engine)
{
	engine->window.mlx = mlx_init();
	if (engine->window.mlx == NULL)
		return (-1);
	get_screen_size(engine);
	engine->window.window = mlx_new_window(engine->window.mlx,
			engine->window.size.x, engine->window.size.y, "miniRT");
	if (engine->window.window == NULL)
		return (-1);
	init_hooks(engine);
	return (0);
}

static void	init_hooks(t_engine *engine)
{
	mlx_hook(engine->window.window, KEY_PRESS, KEY_PRESS_MASK,
		&key_press_handler, engine);
	mlx_hook(engine->window.window, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK,
		&close_engine, engine);
}
