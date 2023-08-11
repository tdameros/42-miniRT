#include "engine.h"
#include "gui/box.h"
#include "gui/utils.h"

static float		get_gui_hidden_ration(t_gui *gui, uint64_t start_time);
static t_vector2i	get_top_box_decal(const t_gui_box *gui_box,
						float hidden_ratio);
static t_vector2i	get_right_box_decal(const t_engine *engine,
						const t_gui_box *gui_box, float hidden_ratio);
static t_vector2i	get_left_box_decal(const t_engine *engine,
						const t_gui_box *gui_box, float hidden_ratio);

void	render_user_interface(t_engine *engine, const uint64_t start_time)
{
	const float	hidden_ratio = get_gui_hidden_ration(&engine->gui, start_time);
	t_vector2i	mouse_position;

	if (hidden_ratio >= 1.f)
		return ;
	mouse_position = get_mouse_position(engine);
	engine->gui.gui_boxes.data[0].draw(engine->gui.gui_boxes.data + 0, engine,
		(t_draw_data){\
			get_top_box_decal(engine->gui.gui_boxes.data + 0, \
				hidden_ratio), \
			mouse_position});
	engine->gui.gui_boxes.data[1].draw(engine->gui.gui_boxes.data + 1, engine,
		(t_draw_data){\
			get_right_box_decal(engine, engine->gui.gui_boxes.data + 1, \
				hidden_ratio), \
			mouse_position});
	engine->gui.gui_boxes.data[2].draw(engine->gui.gui_boxes.data + 2, engine,
		(t_draw_data){\
			get_left_box_decal(engine, engine->gui.gui_boxes.data + 1, \
				hidden_ratio), \
			mouse_position});
	if (engine->gui.current_optional_box >= 0)
		engine->gui.optional_gui_boxes.data[engine->gui.current_optional_box].\
		draw(engine->gui.optional_gui_boxes.data
			+ engine->gui.current_optional_box, engine, (t_draw_data){\
			get_left_box_decal(engine, engine->gui.gui_boxes.data + 1, \
				hidden_ratio), \
			mouse_position});
}

#define TIME_TO_HIDE_GUI 180000.f

static float	get_gui_hidden_ration(t_gui *gui, const uint64_t start_time)
{
	const float	time_passed = start_time
		- gui->hide_animation.start_animation_time;
	const float	time_passed_squared = time_passed * time_passed;

	if (time_passed_squared > TIME_TO_HIDE_GUI)
	{
		gui->hide_animation.hide_animation_finished = true;
		return (gui->hide_animation.is_hidden);
	}
	if (gui->hide_animation.is_hidden)
	{
		return (time_passed_squared / TIME_TO_HIDE_GUI);
	}
	return (1.f - (time_passed_squared) / TIME_TO_HIDE_GUI);
}

static t_vector2i	get_top_box_decal(const t_gui_box *gui_box,
						const float hidden_ratio)
{
	return ((t_vector2i){
		0,
		-((gui_box->size.y + gui_box->position.y) * hidden_ratio)});
}

static t_vector2i	get_right_box_decal(const t_engine *engine,
						const t_gui_box *gui_box, const float hidden_ratio)
{
	return ((t_vector2i){
		(engine->window.size.x - gui_box->position.x) * hidden_ratio,
		0});
}

static t_vector2i	get_left_box_decal(const t_engine *engine,
						const t_gui_box *gui_box, const float hidden_ratio)
{
	return ((t_vector2i){
		-((engine->window.size.x - gui_box->position.x) * hidden_ratio),
		0});
}
