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

#include "engine.h"
#include "events.h"

int	key_release_handler(int key_code, t_engine *engine)
{
	int	i;

	if (key_code != KEY_SPACE && key_code != KEY_L_SHIFT && key_code != KEY_W
		&& key_code != KEY_S && key_code != KEY_A && key_code != KEY_D
		&& key_code != KEY_Q && key_code != KEY_E)
		return (0);
	i = -1;
	while (++i < engine->pressed_keys_index)
	{
		if (engine->pressed_keys[i] == key_code)
		{
			engine->pressed_keys[i]
				= engine->pressed_keys[--engine->pressed_keys_index];
			return (0);
		}
	}
	return (0);
}
