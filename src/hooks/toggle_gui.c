/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_gui.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:46:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/12 11:46:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gui/gui.h"

void	toggle_gui(t_gui *gui)
{
	if (gui->hide_animation.hide_animation_finished)
	{
		gui->hide_animation.is_hidden = !gui->hide_animation.is_hidden;
		gui->draw_gui_image = &put_image_to_image;
		gui->hide_animation.start_animation_time = ft_timeval_to_ms(
				ft_get_current_time());
		gui->hide_animation.hide_animation_finished = false;
	}
}
