/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_toggle_box.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:51:59 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/24 00:52:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"
#include "gui/UI.h"
#include "gui/box.h"

void	draw_toggle_box(t_gui_box *gui_box, const bool is_checkered)
{
	if (gui_box == NULL)
		return ;
	change_image_color(&gui_box->image, COLOR_TRANSPARENT);
	change_image_color(&gui_box->on_hover_image, HOVER_GUI_COLOR);
	if (is_checkered)
	{
		image_draw_check_mark(&gui_box->image, COLOR_WHITE,
			TOGGLE_BOX_BUTTON_OUTLINE_WIDTH);
		image_draw_check_mark(&gui_box->on_hover_image, COLOR_WHITE,
			TOGGLE_BOX_BUTTON_OUTLINE_WIDTH);
	}
	image_draw_outline(&gui_box->image, TOGGLE_BOX_BUTTON_OUTLINE_WIDTH,
		COLOR_BLACK);
	image_draw_outline(&gui_box->on_hover_image,
		TOGGLE_BOX_BUTTON_OUTLINE_WIDTH, COLOR_BLACK);
}
