#include "engine.h"
#include "gui/box.h"
#include "hooks.h"
#include "font/render.h"
#include "gui/UI.h"
#include "ray_tracer_gui_api.h"
#include "events.h"
#include "gui/optional_boxes.h"

static void	delete_box_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data);

void	add_delete_box(t_engine *engine, t_gui_box *gui_box, t_gui_box *parent)
{
	int	y;

	y = 0;
	add_button_box(engine, gui_box, &y, parent);
	if (engine->gui.selected_object.object != NULL)
	{
		write_centered_string_to_image(&engine->gui.font,
			&gui_box->image, "Delete object");
		write_centered_string_to_image(&engine->gui.font,
			&gui_box->on_hover_image, "Delete object");
	}
	else if (engine->gui.selected_object.light != NULL)
	{
		write_centered_string_to_image(&engine->gui.font,
			&gui_box->image, "Delete light");
		write_centered_string_to_image(&engine->gui.font,
			&gui_box->on_hover_image, "Delete light");
	}
	else
	{
		write_centered_string_to_image(&engine->gui.font,
			&gui_box->image, "Error no object or light selected");
		write_centered_string_to_image(&engine->gui.font,
			&gui_box->on_hover_image, "Error no object or light selected");
	}
	gui_box->on_click = &delete_box_on_click;
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
