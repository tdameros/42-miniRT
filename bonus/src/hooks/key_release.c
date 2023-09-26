/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_release.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 22:50:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/07 22:50:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

#include "engine.h"
#include "events.h"
#include "hooks.h"

int	key_release_handler(int key_code, t_engine *engine)
{
	if (key_code == KEY_COMMAND)
	{
		engine->command_key_is_pressed = false;
		mlx_do_key_autorepeaton(engine->window.mlx);
		return (0);
	}
	remove_key_from_pressed_keys(engine, key_code);
	return (0);
}
