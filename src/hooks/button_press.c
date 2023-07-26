/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:55:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/03 17:55:18 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "mlx.h"

#include "engine.h"
#include "gui/box.h"
#include "gui/utils.h"
#include "events.h"
#include "ray_tracer_gui_api.h"
#include "hooks.h"

static int	select_new_object(int button, t_engine *engine, int x, int y);
static int	placing_object(int button, t_engine *engine);
static void	toggle_camera_lock(t_engine *engine);

int	button_press_handler(int button, int x, int y, t_engine *engine)
{
	t_gui_box	*clicked_gui_box;

//	ft_printf("button_code == %d\n\n", button);
	if (button == BUTTON_RIGHT)
		return (toggle_camera_lock(engine), 0);
	if (button != BUTTON_LEFT && button != SCROLL_DOWN &&  button != SCROLL_UP)
		return (0);

	if (engine->object_being_placed.object != NULL
		|| engine->object_being_placed.light != NULL)
		return (placing_object(button, engine));
	clicked_gui_box = get_clicked_gui_box(engine->gui.gui_boxes, &x, &y);
	if (clicked_gui_box == NULL)
		return (select_new_object(button, engine, x, y));
	if (clicked_gui_box->on_click != NULL)
		clicked_gui_box->on_click(clicked_gui_box, engine,
			(t_click_data){(t_vector2i){x, y}, button});
	return (0);
}

static int	placing_object(int button, t_engine *engine)
{
	if (button == SCROLL_DOWN)
	{
		engine->object_being_placed_distance -= 0.5f;
		engine->scene_changed = true;
		return (0);
	}
	else if (button == SCROLL_UP)
	{
		engine->object_being_placed_distance += 0.5f;
		engine->scene_changed = true;
		return (0);
	}
	else if (button != BUTTON_LEFT)
		return (0);
	update_float_input_boxes(engine);
	ft_bzero(&engine->object_being_placed, sizeof(engine->object_being_placed));
	return (0);
}

static int	select_new_object(int button, t_engine *engine, int x, int y)
{
	if (button != BUTTON_LEFT || x < 0 || y < 0
		|| x >= engine->ray_traced_image.width
		|| y >= engine->ray_traced_image.height)
		return (0);
	engine->gui.selected_object.object = get_clicked_object(engine, x, y);
	engine->gui.selected_object.light = NULL;

	if (engine->gui.selected_object.object == NULL)
		return (update_object_attributes_modification_box(engine));
	update_color_picker_color(&engine->gui);
	redraw_icons(engine, engine->gui.selected_object.object->material);
	return (update_object_attributes_modification_box(engine));
}

static void	toggle_camera_lock(t_engine *engine)
{
	const t_vector2i	screen_center = {
		.x = engine->ray_traced_image.width / 2,
		.y = engine->ray_traced_image.height / 2
	};

	mlx_mouse_move(engine->window.window, screen_center.x, screen_center.y);
	if (engine->camera.lock == true)
	{
		if (engine->gui.is_hidden == false)
		{
			toggle_gui(&engine->gui);
			engine->gui.should_show_gui_on_camera_lock = true;
		}
		else
			engine->gui.should_show_gui_on_camera_lock = false;
		engine->previous_mouse_position = screen_center;
		engine->camera.lock = false;
		mlx_mouse_hide();
		return ;
	}
	if (engine->gui.should_show_gui_on_camera_lock && engine->gui.is_hidden)
		toggle_gui(&engine->gui);
	engine->camera.lock = true;
	mlx_mouse_show();
}
