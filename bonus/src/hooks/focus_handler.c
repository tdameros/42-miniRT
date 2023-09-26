/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   focus_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 03:02:50 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/24 03:02:50 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "mlx_wrapper.h"

int	focus_in_handler(t_engine *engine)
{
	if (engine->camera.lock == false)
		mouse_hide(engine);
	engine->window.is_focused = true;
	return (0);
}

int	focus_out_handler(t_engine *engine)
{
	if (engine->camera.lock == false)
		mouse_show(engine);
	engine->window.is_focused = false;
	return (0);
}
