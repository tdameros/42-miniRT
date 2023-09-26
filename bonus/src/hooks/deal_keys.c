/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 07:03:56 by vfries            #+#    #+#             */
/*   Updated: 2023/09/24 07:07:45 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "engine.h"

#define TIME_FOR_FULL_DEFAULT_MOVEMENT_MS 25
#define DEFAULT_MOUVEMENT 0.4f

static void	deal_key(t_engine *engine, const float movement, const int i);

void	deal_keys(t_engine *engine, const uint64_t start_time)
{
	const float	time_since_last_frame = start_time
		- engine->last_frame_start_time;
	const float	movement_ratio = time_since_last_frame
		/ TIME_FOR_FULL_DEFAULT_MOVEMENT_MS;
	const float	movement = DEFAULT_MOUVEMENT * movement_ratio;
	int			i;

	i = 0;
	while (i < engine->pressed_keys_index)
		deal_key(engine, movement, i++);
}

static void	deal_key(t_engine *engine, const float movement, const int i)
{
	if (engine->pressed_keys[i] == KEY_W)
		camera_move_forward(&engine->camera, movement);
	else if (engine->pressed_keys[i] == KEY_S)
		camera_move_forward(&engine->camera, -movement);
	else if (engine->pressed_keys[i] == KEY_A)
		camera_move_left(&engine->camera, movement);
	else if (engine->pressed_keys[i] == KEY_D)
		camera_move_left(&engine->camera, -movement);
	else if (engine->pressed_keys[i] == KEY_SPACE)
		camera_move_up(&engine->camera, movement);
	else if (engine->pressed_keys[i] == KEY_L_SHIFT)
		camera_move_up(&engine->camera, -movement);
	else if (engine->pressed_keys[i] == KEY_Q)
		camera_peek(&engine->camera, -movement * 10.f);
	else if (engine->pressed_keys[i] == KEY_E)
		camera_peek(&engine->camera, movement * 10.f);
}
