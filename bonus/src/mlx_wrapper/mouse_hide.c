/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hide.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 03:04:22 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/24 03:04:34 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

#include "engine.h"

#ifdef __APPLE__

int	mouse_hide(t_engine *engine)
{
	return (mlx_mouse_hide());
	(void)engine;
}
#endif
#ifdef __linux__

int	mouse_hide(t_engine *engine)
{
	return (mlx_mouse_hide(engine->window.mlx, engine->window.window));
}
#endif
