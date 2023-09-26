/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_settings_icon.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:22:26 by vfries            #+#    #+#             */
/*   Updated: 2023/07/30 17:23:04 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "libft.h"

#include "gui/box.h"
#include "gui/main_gui_box.h"
#include "engine.h"
#include "colors.h"
#include "gui/UI.h"
#include "events.h"

static void	write_setting_icon(t_image *image, unsigned int color);
static void	settings_icon_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data);

void	init_settings_icon(t_engine *engine, t_gui_box *gui_box)
{
	init_image(&gui_box->image, &engine->window, gui_box->size.x,
		gui_box->size.y);
	init_image(&gui_box->on_hover_image, &engine->window, gui_box->size.x,
		gui_box->size.y);
	gui_box->on_click = &settings_icon_on_click;
	write_setting_icon(&gui_box->image, COLOR_TRANSPARENT);
	write_setting_icon(&gui_box->on_hover_image, HOVER_GUI_COLOR);
	round_image_corners(&gui_box->on_hover_image, BOX_ROUNDING_RADIUS);
}

static void	write_setting_icon(t_image *image, const unsigned int color)
{
	const float	circle_diameter
		= ft_get_smallest_int(image->width, image->height)
		* 0.65f;
	const float	circle_radius = circle_diameter / 2.f;
	float		theta;

	change_image_color(image, color);
	image_draw_circle(image, (t_vector2f){\
			.x = image->width / 2, \
			.y = image->height / 2},
		circle_radius, MENU_BOX_ICONS_COLOR);
	theta = M_PI / 2.f;
	while (theta < M_PI * 2.f + M_PI / 2.f)
	{
		image_draw_circle(image, (t_vector2f){\
				.x = image->width / 2.f + circle_radius * cosf(theta), \
				.y = image->height / 2.f + circle_radius * sinf(theta)},
			circle_radius * 0.42f, MENU_BOX_ICONS_COLOR);
		theta += M_PI * 2.f / 6.f;
	}
	image_draw_circle(image, (t_vector2f){\
			.x = image->width / 2, \
			.y = image->height / 2},
		circle_diameter / 2.4f, color);
}

static void	settings_icon_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data)
{
	(void)self;
	if (click_data.button != BUTTON_LEFT)
		return ;
	if (engine->gui.current_optional_box == SETTINGS_BOX)
		engine->gui.current_optional_box = NO_OPTIONAL_BOX;
	else
		engine->gui.current_optional_box = SETTINGS_BOX;
}
