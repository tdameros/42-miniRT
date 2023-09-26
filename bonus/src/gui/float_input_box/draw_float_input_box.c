/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_float_input_box.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:30:59 by vincent           #+#    #+#             */
/*   Updated: 2023/07/29 19:31:17 by vincent          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gui/UI.h"
#include "gui/utils.h"

void	draw_center_box_image(t_image *image)
{
	change_image_color(image, SUB_GUI_COLOR);
	image_draw_top_outline(image, 2, COLOR_BLACK);
	image_draw_bottom_outline(image, 2, COLOR_BLACK);
}
