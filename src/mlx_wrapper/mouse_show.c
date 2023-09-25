/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_show.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 03:04:58 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/24 03:04:58 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

#include "engine.h"

#ifdef __APPLE__

int	mouse_show(t_engine *engine)
{
	return (mlx_mouse_show());
	(void)engine;
}
#endif
#ifdef __linux__

int	mouse_show(t_engine *engine)
{
	return (mlx_mouse_show(engine->window.mlx, engine->window.window));
}
#endif
