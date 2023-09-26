/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_clicks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 23:02:45 by vfries            #+#    #+#             */
/*   Updated: 2023/09/23 23:10:01 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui/object_modification_box.h"
#include "events.h"
#include "hooks.h"

static void	handle_object_is_null(t_engine *engine, const t_color albedo);

void	base_color_picker_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	const unsigned int	uint_color = get_image_pixel_color(&self->image,
			click_data.click_position.y, click_data.click_position.x);
	t_color				albedo;

	if (click_data.button != BUTTON_LEFT || uint_color == COLOR_TRANSPARENT)
		return ;
	engine->gui.color_and_material.color_picker_base_color
		= get_t_color_from_uint(uint_color);
	engine->gui.color_and_material.color_picker_base_color_was_changed
		= true;
	albedo = vector3f_divide(engine->gui.color_and_material.\
		color_picker_base_color, 255.f);
	if (engine->gui.selected_object.object == NULL)
		return (handle_object_is_null(engine, albedo));
	if (engine->gui.color_and_material.color_being_changed
		== OUTLINE_CHECKERBOARD_COLOR)
		engine->gui.selected_object.object->material.textures.\
			outline.checkerboard.albedo = albedo;
	else if (engine->gui.color_and_material.color_being_changed
		== CAP_CHECKERBOARD_COLOR)
		engine->gui.selected_object.object->material.textures.\
			cap.checkerboard.albedo = albedo;
	else
		engine->gui.selected_object.object->material.albedo = albedo;
	redraw_icons(engine, engine->gui.selected_object.object, NULL);
}

void	color_picker_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data)
{
	const unsigned int	uint_color = get_image_pixel_color(&self->image,
			click_data.click_position.y, click_data.click_position.x);
	const t_color		albedo = vector3f_divide(
			get_t_color_from_uint(uint_color), 255.f);

	if (click_data.button != BUTTON_LEFT || uint_color == COLOR_TRANSPARENT)
		return ;
	if (engine->gui.selected_object.object == NULL)
		return (handle_object_is_null(engine, albedo));
	if (engine->gui.color_and_material.color_being_changed
		== OUTLINE_CHECKERBOARD_COLOR)
		engine->gui.selected_object.object->material.textures.\
			outline.checkerboard.albedo = albedo;
	else if (engine->gui.color_and_material.color_being_changed
		== CAP_CHECKERBOARD_COLOR)
		engine->gui.selected_object.object->material.textures.\
			cap.checkerboard.albedo = albedo;
	else
		engine->gui.selected_object.object->material.albedo = albedo;
	redraw_icons(engine, engine->gui.selected_object.object, NULL);
}

static void	handle_object_is_null(t_engine *engine, const t_color albedo)
{
	t_light	tmp_light;

	if (engine->gui.selected_object.light == NULL)
	{
		tmp_light.color = albedo;
		return (redraw_icons(engine, NULL, &tmp_light));
	}
	engine->scene_changed = true;
	light_set_color(engine->gui.selected_object.light, albedo);
	return (redraw_icons(engine, NULL, engine->gui.selected_object.light));
}
