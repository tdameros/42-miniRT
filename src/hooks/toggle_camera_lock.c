/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_camera_lock.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 09:14:02 by vfries            #+#    #+#             */
/*   Updated: 2023/09/24 09:19:59 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "hooks.h"
#include "mlx_wrapper.h"

static void	unlock_camera(t_engine *engine);
static void	lock_camera(t_engine *engine);

void	toggle_camera_lock(t_engine *engine)
{
	const t_vector2i	screen_center = {
		.x = engine->ray_traced_image.width / 2,
		.y = engine->ray_traced_image.height / 2};

	mouse_move(engine, screen_center);
	if (engine->camera.lock)
		return (unlock_camera(engine));
	lock_camera(engine);
}

static void	unlock_camera(t_engine *engine)
{
	if (engine->gui.hide_animation.is_hidden == false)
	{
		toggle_gui(&engine->gui);
		engine->gui.should_show_gui_on_camera_lock = true;
	}
	else
		engine->gui.should_show_gui_on_camera_lock = false;
	engine->previous_mouse_position = engine->mouse_position;
	engine->camera.lock = false;
	mouse_hide(engine);
	if (engine->object_being_placed.light
		|| engine->object_being_placed.object)
		engine->scene_changed = true;
}

static void	lock_camera(t_engine *engine)
{
	if (engine->gui.should_show_gui_on_camera_lock
		&& engine->gui.hide_animation.is_hidden)
		toggle_gui(&engine->gui);
	engine->camera.lock = true;
	mouse_show(engine);
}
