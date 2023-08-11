/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:37:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/30 18:37:01 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "engine.h"
#include "hooks.h"
#include "export.h"

int	key_press_handler(int key_code, t_engine *engine)
{
	int	i;

	if (key_code == KEY_ESC)
		close_engine(engine);
	else if (key_code == KEY_H)
		toggle_gui(&engine->gui);
	else if (key_code == KEY_T)
	{
		if (take_screenshot(&engine->ray_traced_image) < 0)
			ft_print_error("An error has occurred during the screenshot.\n");
		else
			engine->gui.screen_shot.last_screen_shot
				= ft_get_current_time_in_ms();
	}
	else if (key_code == KEY_G)
	{
		if (export_scene(engine, "exported_scene.rt") < 0)
			ft_print_error("An error has occurred during export.\n");
	}
	if (key_code != KEY_W && key_code != KEY_S && key_code != KEY_A
		&& key_code != KEY_D && key_code != KEY_SPACE && key_code != KEY_L_SHIFT
		&& key_code != KEY_Q && key_code != KEY_E)
		return (0);
	i = -1;
	while (++i < engine->pressed_keys_index)
		if (key_code == engine->pressed_keys[i])
			return (0);
	engine->pressed_keys[engine->pressed_keys_index++] = key_code;
	return (0);
}
