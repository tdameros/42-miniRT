/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_click.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:25:09 by vfries            #+#    #+#             */
/*   Updated: 2023/09/01 18:25:10 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "gui/box.h"

void	outline_picker_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	(void)self;
	if (click_data.button != BUTTON_LEFT)
		return ;
	engine->gui.color_and_material.texture_being_changed = OUTLINE_TEXTURE;
}

void	cap_picker_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	(void)self;
	if (click_data.button != BUTTON_LEFT)
		return ;
	engine->gui.color_and_material.texture_being_changed = CAP_TEXTURE;
}
