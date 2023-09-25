/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_user_interface.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 03:02:21 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/24 03:55:20 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "mlx_wrapper.h"
#include "engine.h"
#include "gui/box.h"
#include "render_frame.h"
#include "gui/utils.h"

static void			render_main_gui_boxes(t_engine *engine);
static float		get_gui_hidden_ration(t_gui *gui, uint64_t start_time);

void	render_user_interface(t_engine *engine, const uint64_t start_time)
{
	engine->gui.hide_animation.current_hidden_ratio
		= get_gui_hidden_ration(&engine->gui, start_time);
	if (engine->gui.hide_animation.current_hidden_ratio >= 1.f)
		return ;
	render_main_gui_boxes(engine);
	if (engine->gui.current_optional_box >= 0
		&& engine->gui.current_optional_box < NUMBER_OF_OPTIONAL_BOXES
		&& engine->gui.optional_gui_boxes.data \
		[engine->gui.current_optional_box].draw != NULL)
		engine->gui.optional_gui_boxes.data[engine->gui.current_optional_box].\
		draw(engine->gui.optional_gui_boxes.data
			+ engine->gui.current_optional_box, engine, (t_draw_data){\
			get_left_box_decal(engine, engine->gui.gui_boxes.data + 1),
			engine->mouse_position});
	render_message(engine);
}

static void	render_main_gui_boxes(t_engine *engine)
{
	engine->gui.gui_boxes.data[0].draw(engine->gui.gui_boxes.data + 0, engine,
		(t_draw_data){\
			get_top_box_decal(engine, engine->gui.gui_boxes.data + 0), \
			engine->mouse_position});
	engine->gui.gui_boxes.data[1].draw(engine->gui.gui_boxes.data + 1, engine,
		(t_draw_data){\
			get_right_box_decal(engine, engine->gui.gui_boxes.data + 1), \
			engine->mouse_position});
	engine->gui.gui_boxes.data[2].draw(engine->gui.gui_boxes.data + 2, engine,
		(t_draw_data){\
			get_left_box_decal(engine, engine->gui.gui_boxes.data + 1), \
			engine->mouse_position});
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
		if (gui->hide_animation.is_hidden == false)
			gui->draw_gui_image = &put_image_to_image_unsafe;
		return (gui->hide_animation.is_hidden);
	}
	if (gui->hide_animation.is_hidden)
	{
		return (time_passed_squared / TIME_TO_HIDE_GUI);
	}
	return (1.f - (time_passed_squared) / TIME_TO_HIDE_GUI);
}
