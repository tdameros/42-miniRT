/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pressed_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 03:04:15 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/24 03:04:16 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "events.h"

static bool	is_allowed_key(const int key_code);

void	add_key_to_pressed_keys(t_engine *engine, const int key_code)
{
	int	i;

	if (is_allowed_key(key_code) == false)
		return ;
	i = -1;
	while (++i < engine->pressed_keys_index)
		if (key_code == engine->pressed_keys[i])
			return ;
	engine->pressed_keys[engine->pressed_keys_index++] = key_code;
}

void	remove_key_from_pressed_keys(t_engine *engine, const int key_code)
{
	int	i;

	if (is_allowed_key(key_code) == false)
		return ;
	i = -1;
	while (++i < engine->pressed_keys_index)
	{
		while (engine->pressed_keys[i] == key_code
			&& i < engine->pressed_keys_index)
		{
			engine->pressed_keys[i]
				= engine->pressed_keys[--engine->pressed_keys_index];
		}
	}
}

void	clear_pressed_keys(t_engine *engine)
{
	engine->pressed_keys_index = 0;
}

static bool	is_allowed_key(const int key_code)
{
	return (key_code == KEY_SPACE || key_code == KEY_L_SHIFT
		|| key_code == KEY_W || key_code == KEY_S || key_code == KEY_A
		|| key_code == KEY_D || key_code == KEY_Q || key_code == KEY_E);
}
