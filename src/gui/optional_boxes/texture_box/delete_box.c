#include "gui/box.h"
#include "gui/UI.h"
#include "gui/optional_boxes.h"
#include "font/render.h"
#include "hooks.h"

static void	delete_box_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data);
static void	delete_cap(t_object *object, bool is_normal_map);
static void	delete_outline(t_object *object, bool is_normal_map);

void	init_delete_box(t_engine *engine, t_gui_box *delete_box)
{
	engine->gui.color_and_material.delete_texture_normal_map_box = delete_box;
	init_image(&delete_box->image, &engine->window, delete_box->size.x,
		delete_box->size.y);
	init_image(&delete_box->on_hover_image, &engine->window, delete_box->size.x,
		delete_box->size.y);
	update_delete_box(engine);
}

void	update_delete_box(t_engine *engine)
{
	const bool	is_normal_map = engine->gui.color_and_material.\
		changing_normal_map_or_texture == NORMAL_MAP;
	char		*message_to_display;
	t_gui_box	*delete_box;

	delete_box = engine->gui.color_and_material.delete_texture_normal_map_box;
	if (is_normal_map)
		message_to_display = "Delete normal map";
	else
		message_to_display = "Delete texture";
	change_image_color(&delete_box->image, SUB_GUI_COLOR);
	write_centered_string_to_image(&engine->gui.font, &delete_box->image,
		message_to_display);
	round_image_corners(&delete_box->image, BOX_ROUNDING_RADIUS);
	change_image_color(&delete_box->on_hover_image, HOVER_GUI_COLOR);
	write_centered_string_to_image(&engine->gui.font,
		&delete_box->on_hover_image, message_to_display);
	round_image_corners(&delete_box->on_hover_image, BOX_ROUNDING_RADIUS);
	delete_box->on_click = &delete_box_on_click;
}

static void	delete_box_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data)
{
	t_object	*object;
	const bool	is_cap = engine->gui.color_and_material.texture_being_changed
		== CAP_TEXTURE;
	const bool	is_normal_map = engine->gui.color_and_material.\
		changing_normal_map_or_texture == NORMAL_MAP;

	(void)click_data;
	(void)self;
	object = engine->gui.selected_object.object;
	if (object == NULL)
		return ;
	if (is_cap)
		delete_cap(object, is_normal_map);
	else
		delete_outline(object, is_normal_map);
	redraw_icons(engine, object, NULL);
	engine->scene_changed = true;
}

static void	delete_cap(t_object *object, const bool is_normal_map)
{
	if (is_normal_map)
		free_cap_normals_map(&object->material);
	else
		free_cap_texture(&object->material);
}

static void	delete_outline(t_object *object, const bool is_normal_map)
{
	if (is_normal_map)
		free_outline_normals_map(&object->material);
	else
		free_outline_texture(&object->material);
}
