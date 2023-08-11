#include "engine.h"
#include "gui/box.h"
#include "hooks.h"
#include "events.h"
#include "font/render.h"

static void	antialiasing_toggle_box_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data);

void	init_antialiasing_toggle_box(t_engine *engine, t_gui_box *gui_box,
			int *y, t_gui_box *parent)
{
	add_toggle_box(engine, gui_box, y, parent);
	draw_toggle_box(gui_box->children.data + 0, engine->antialiasing);
	change_image_color(&gui_box->children.data[1].image, COLOR_TRANSPARENT);
	write_centered_string_to_image(&engine->gui.font,
		&gui_box->children.data[1].image, "Antialiasing");
	gui_box->children.data->on_click = &antialiasing_toggle_box_on_click;
}

static void	antialiasing_toggle_box_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data)
{
	(void)self;
	if (click_data.button != BUTTON_LEFT)
		return ;
	engine->antialiasing = !engine->antialiasing;
	engine->scene_changed = true;
	draw_toggle_box(self, engine->antialiasing);
}
