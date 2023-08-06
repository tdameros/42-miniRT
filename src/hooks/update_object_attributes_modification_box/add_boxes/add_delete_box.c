#include "engine.h"
#include "gui/box.h"
#include "hooks.h"
#include "font/render.h"
#include "gui/UI.h"
#include "ray_tracer_gui_api.h"
#include "events.h"

static void	draw_button(t_gui_box *gui_box);
static void	delete_box_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data);

void	add_delete_box(t_engine *engine, t_gui_box *gui_box, t_gui_box *parent)
{
	int	i;

	i = 0;
	add_toggle_box(engine, gui_box, &i, parent);
	gui_box->children.data->on_click = &delete_box_on_click;
	draw_button(gui_box->children.data);
	change_image_color(&gui_box->children.data[1].image, COLOR_TRANSPARENT);
	if (engine->gui.selected_object.object != NULL)
		write_centered_string_to_image(&engine->gui.font,
			&gui_box->children.data[1].image, "Delete object");
	else if (engine->gui.selected_object.light != NULL)
		write_centered_string_to_image(&engine->gui.font,
			&gui_box->children.data[1].image, "Delete light");
	else
		write_centered_string_to_image(&engine->gui.font,
			&gui_box->children.data[1].image,
			"Error no object or light selected");
}

static void	draw_button(t_gui_box *gui_box)
{
	change_image_color(&gui_box->image, COLOR_TRANSPARENT);
	change_image_color(&gui_box->on_hover_image, HOVER_GUI_COLOR);
	image_draw_outline(&gui_box->image, TOGGLE_BOX_BUTTON_OUTLINE_WIDTH,
		COLOR_BLACK);
	image_draw_outline(&gui_box->on_hover_image,
		TOGGLE_BOX_BUTTON_OUTLINE_WIDTH, COLOR_BLACK);
}

static void	delete_box_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data)
{
	size_t	index;

	(void)self;
	if (click_data.button != BUTTON_LEFT
		|| (engine->gui.selected_object.object == NULL
			&& engine->gui.selected_object.light == NULL))
		return ;
	engine->scene_changed = true;
	if (engine->gui.selected_object.object == NULL)
	{
		index = engine->gui.selected_object.light - engine->scene.lights.data;
		remove_light(engine, index);
		engine->gui.selected_object.light = NULL;
		update_object_attributes_modification_box(engine);
		return ;
	}
	index = engine->gui.selected_object.object - engine->scene.objects.data;
	remove_object(engine, index);
	engine->gui.selected_object.object = NULL;
	update_object_attributes_modification_box(engine);
}
