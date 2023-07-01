/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_release.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 04:26:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/01 04:26:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "events.h"
#include "ray_tracer_gui_api.h"
#include "hooks.h"
#include "mlx.h"

int	button_release_handler(int button, int x, int y, t_engine *engine)
{
	(void) x;
	(void) y;
	if (button == BUTTON_RIGHT)
	{
		engine->camera.lock = true;
//		mlx_mouse_move(engine->window.window, 100, 100);
		mlx_mouse_show();
	}
	return (0);
}
