#include "engine.h"
#include "gui/box.h"

static void	update_gui_hidden_ration(t_gui *gui);
static int	get_y_decal(const t_gui_box *gui_box, const t_gui *gui);
static int	get_x_decal(const t_engine *engine, const t_gui_box *gui_box,
				const t_gui *gui);

void	render_user_interface(t_engine *engine)
{
	update_gui_hidden_ration(&engine->gui);
	if (engine->gui.hidden_ratio == 1.0)
		return ;
	engine->gui.gui_boxes.data[0].draw(engine->gui.gui_boxes.data + 0, engine,
		0, get_y_decal(engine->gui.gui_boxes.data + 0, &engine->gui));
	engine->gui.gui_boxes.data[1].draw(engine->gui.gui_boxes.data + 1, engine,
		get_x_decal(engine, engine->gui.gui_boxes.data + 1, &engine->gui), 0);
}

#define HIDDEN_RATIO_DIVIDER 45
#define HIDDEN_RATION_ADDER 0.0050

static void	update_gui_hidden_ration(t_gui *gui)
{
	if (gui->is_hidden && gui->hidden_ratio < 1.0)
	{
		gui->hidden_ratio += (1.0 - gui->hidden_ratio)
			/ HIDDEN_RATIO_DIVIDER + HIDDEN_RATION_ADDER;
		if (gui->hidden_ratio > 1.0)
			gui->hidden_ratio = 1.0;
		gui->draw_gui_image = &put_image_to_image;
	}
	else if (gui->is_hidden == false && gui->hidden_ratio > 0.0)
	{
		gui->hidden_ratio -= gui->hidden_ratio
			/ HIDDEN_RATIO_DIVIDER + HIDDEN_RATION_ADDER;
		if (gui->hidden_ratio <= 0.0)
		{
			gui->draw_gui_image = &put_image_to_image_unsafe;
			gui->hidden_ratio = 0.0;
		}
	}
}

static int	get_y_decal(const t_gui_box *gui_box, const t_gui *gui)
{
	return ((int)-((gui_box->size.y + gui_box->position.y)
			* gui->hidden_ratio));
}

static int	get_x_decal(const t_engine *engine, const t_gui_box *gui_box,
				const t_gui *gui)
{
	return ((int)((engine->window.size.x - gui_box->position.x)
		* gui->hidden_ratio));
}
