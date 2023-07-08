#include "engine.h"
#include "gui/box.h"

static float	get_gui_hidden_ration(t_gui *gui, uint64_t start_time);
static int		get_y_decal(const t_gui_box *gui_box, float hidden_ratio);
static int		get_x_decal(const t_engine *engine, const t_gui_box *gui_box,
					float hidden_ratio);

void	render_user_interface(t_engine *engine, const uint64_t start_time)
{
	const float	hidden_ratio = get_gui_hidden_ration(&engine->gui, start_time);

	if (hidden_ratio >= 1.f)
		return ;
	engine->gui.gui_boxes.data[0].draw(engine->gui.gui_boxes.data + 0, engine,
		0, get_y_decal(engine->gui.gui_boxes.data + 0, hidden_ratio));
	engine->gui.gui_boxes.data[1].draw(engine->gui.gui_boxes.data + 1, engine,
		get_x_decal(engine, engine->gui.gui_boxes.data + 1, hidden_ratio), 0);
}

#define TIME_TO_HIDE_GUI 180000.f

static float	get_gui_hidden_ration(t_gui *gui, const uint64_t start_time)
{
	const float	time_passed = start_time - gui->start_animation_time;
	const float	time_passed_squared = time_passed * time_passed;

	if (time_passed_squared > TIME_TO_HIDE_GUI)
		return (gui->is_hidden);
	if (gui->is_hidden)
	{
		return (time_passed_squared / TIME_TO_HIDE_GUI);
	}
	return (1.f - (time_passed_squared) / TIME_TO_HIDE_GUI);
}

static int	get_y_decal(const t_gui_box *gui_box, const float hidden_ratio)
{
	return (-((gui_box->size.y + gui_box->position.y) * hidden_ratio));
}

static int	get_x_decal(const t_engine *engine, const t_gui_box *gui_box,
				const float hidden_ratio)
{
	return (((engine->window.size.x - gui_box->position.x) * hidden_ratio));
}
