/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_color_picker_box.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:23:59 by vfries            #+#    #+#             */
/*   Updated: 2023/07/30 18:24:04 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <math.h>

#include "mlx_wrapper.h"
#include "gui/box.h"
#include "gui/utils.h"
#include "gui/object_modification_box.h"
#include "hooks.h"
#include "events.h"

static void			color_picker_draw(t_gui_box *self, t_engine *engine,
						t_draw_data draw_data);
static void			update_image(t_gui_box *self, t_engine *engine);
static unsigned int	get_darker_color(float x, float limit,
						t_color base_color);
static unsigned int	get_lighter_color(float x, float limit, float start,
						t_color base_color);
static void			color_picker_on_click(t_gui_box *self, t_engine *engine,
						t_click_data click_data);

void	init_color_picker_box(t_engine *engine, t_gui_box *gui_box,
			t_gui_box *parent)
{
	*gui_box = create_t_gui_box(engine, (t_gui_box_create){parent, \
		(t_vector2i){
			.x = 0,
			.y = 0}, \
		(t_vector2i){
			.x = parent->size.x,
			.y = parent->size.y / 2 - 4}, \
		true});
	init_image(&gui_box->on_hover_image,
		&engine->window, parent->size.x, parent->size.y / 2 - 4);
	gui_box->draw = &color_picker_draw;
	gui_box->on_click = &color_picker_on_click;
}

static void	color_picker_draw(t_gui_box *self, t_engine *engine,
				t_draw_data draw_data)
{
	const t_vector2i	position = {self->position.x + draw_data.offset.x,
		self->position.y + draw_data.offset.y};

	if (engine->gui.color_and_material.color_picker_base_color_was_changed)
	{
		update_image(self, engine);
		engine->gui.color_and_material.color_picker_base_color_was_changed
			= false;
	}
	put_image(engine, &self->image, position);
	if (is_mouse_hovering_box(self, draw_data.offset, &self->image,
			draw_data.mouse_position) == false)
		return ;
	add_hover_color_circle(self, draw_data.offset, draw_data.mouse_position);
	put_image(engine, &self->on_hover_image, position);
}

static void	update_image(t_gui_box *self, t_engine *engine)
{
	int	y;
	int	x;
	int	limit;

	y = -1;
	while (++y < self->image.height)
	{
		x = -1;
		limit = (int)roundf((float)self->image.width / 2);
		while (++x < limit)
			put_pixel_on_image(&self->image, y, x, get_darker_color(x, limit, \
				engine->gui.color_and_material.color_picker_base_color));
		x--;
		while (++x < self->image.width)
			put_pixel_on_image(&self->image, y, x, get_lighter_color(x, \
				self->image.width, limit, \
				engine->gui.color_and_material.color_picker_base_color));
	}
	round_image_corners(&self->image, 10);
}

static unsigned int	get_darker_color(float x, float limit,
						t_color base_color)
{
	const t_color	color = {
		.x = roundf(base_color.x * x / limit),
		.y = roundf(base_color.y * x / limit),
		.z = roundf(base_color.z * x / limit),
	};

	return (rgb_to_uint(color));
}

static unsigned int	get_lighter_color(float x, float limit, float start,
						t_color base_color)
{
	const t_color	color = {
		.x = roundf(base_color.x
			+ (255.f - base_color.x) * (x - start) / (limit - start)),
		.y = roundf(base_color.y
			+ (255.f - base_color.y) * (x - start) / (limit - start)),
		.z = roundf(base_color.z
			+ (255.f - base_color.z) * (x - start) / (limit - start)),
	};

	return (rgb_to_uint(color));
}

static void	color_picker_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data)
{
	const unsigned int	uint_color = get_image_pixel_color(&self->image,
			click_data.click_position.y, click_data.click_position.x);
	const t_color		albedo = vector3f_divide(
			get_t_color_from_uint(uint_color), 255.f);
	t_light				tmp_light;

	if (click_data.button != BUTTON_LEFT || uint_color == COLOR_TRANSPARENT)
		return ;
	if (engine->gui.selected_object.object == NULL
		&& engine->gui.selected_object.light == NULL)
	{
		tmp_light.color = albedo;
		return (redraw_icons(engine, NULL, &tmp_light));
	}
	engine->scene_changed = true;
	if (engine->gui.selected_object.object == NULL)
	{
		light_set_color(engine->gui.selected_object.light, albedo);
		return (redraw_icons(engine, NULL, engine->gui.selected_object.light));
	}
	if (engine->gui.color_and_material.color_being_changed == OUTLINE_CHECKERBOARD_COLOR)
		engine->gui.selected_object.object->material.textures.\
			outline.checkerboard.albedo = albedo;
	else if (engine->gui.color_and_material.color_being_changed == CAP_CHECKERBOARD_COLOR)
		engine->gui.selected_object.object->material.textures.\
			cap.checkerboard.albedo = albedo;
	else
		engine->gui.selected_object.object->material.albedo = albedo;
	redraw_icons(engine, engine->gui.selected_object.object, NULL);
}
