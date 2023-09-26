/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_message_to_screen.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 22:20:44 by vfries            #+#    #+#             */
/*   Updated: 2023/09/25 22:29:30 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "font/render.h"

void	write_message_to_screen(t_engine *engine, const char *message)
{
	change_image_color(&engine->gui.message.image_with_message,
		COLOR_TRANSPARENT);
	engine->gui.message.animation_start_time_ms = ft_get_current_time_in_ms();
	engine->gui.message.time_to_appear_ms = 500;
	engine->gui.message.time_to_display_ms = 1000;
	engine->gui.message.time_to_disappear_ms = 500;
	write_centered_string_to_image(&engine->gui.font,
		&engine->gui.message.image_with_message, message);
}
