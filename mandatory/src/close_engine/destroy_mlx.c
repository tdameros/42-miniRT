/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:09:09 by vfries            #+#    #+#             */
/*   Updated: 2023/09/25 19:10:10 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "mlx.h"

#if defined(__APPLE__)

void	destroy_mlx(t_engine *engine)
{
	if (engine->window.mlx != NULL && engine->window.window != NULL)
		mlx_destroy_window(engine->window.mlx, engine->window.window);
}

#elif defined(__linux__)

void	destroy_mlx(t_engine *engine)
{
	if (engine->window.mlx != NULL && engine->window.window != NULL)
		mlx_destroy_window(engine->window.mlx, engine->window.window);
	if (engine->window.mlx != NULL)
		mlx_destroy_display(engine->window.mlx);
}

#else
# error "Unsuported OS"
#endif
