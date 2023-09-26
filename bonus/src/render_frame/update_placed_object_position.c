/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_placed_object_position.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 07:22:11 by vfries            #+#    #+#             */
/*   Updated: 2023/09/24 07:49:04 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "object.h"
#include "hooks.h"
#include "mlx_wrapper.h"
#include "ray_tracer_gui_api.h"

static bool	should_update_position(t_engine *engine);
static void	update_object_position(t_engine *engine,
				const t_vector3f direction);
static void	update_light_position(t_engine *engine, const t_vector3f direction);
static void	update_mouse_position(t_engine *engine, t_vector2i *mouse_position);

void	update_placed_object_position(t_engine *engine)
{
	size_t		ray_index;
	t_vector3f	direction;

	if (should_update_position(engine) == false)
		return ;
	engine->scene_changed = true;
	update_mouse_position(engine, &engine->mouse_position);
	engine->previous_mouse_position = engine->mouse_position;
	ray_index = engine->mouse_position.x + engine->mouse_position.y \
			* (int)engine->camera.viewport.size.x;
	direction = engine->camera.rays[ray_index].direction;
	if (engine->object_being_placed.object != NULL)
		update_object_position(engine, direction);
	else
		update_light_position(engine, direction);
}

static bool	should_update_position(t_engine *engine)
{
	float		yaw_delta;
	float		pitch_delta;

	if ((engine->object_being_placed.object == NULL
			&& engine->object_being_placed.light == NULL)
		|| engine->window.is_focused == false)
		return (false);
	engine->mouse_position = engine->mouse_position;
	yaw_delta = (engine->previous_mouse_position.x - engine->mouse_position.x)
		* engine->camera.rotation_speed;
	pitch_delta = (engine->previous_mouse_position.y - engine->mouse_position.y)
		* engine->camera.rotation_speed;
	if (yaw_delta == 0 && pitch_delta == 0 && engine->scene_changed == false)
		return (false);
	return (true);
}

static void	update_object_position(t_engine *engine, const t_vector3f direction)
{
	object_set_position(engine->object_being_placed.object, vector3f_add(
			engine->camera.position,
			vector3f_multiply(direction,
				engine->object_being_placed_distance)));
	update_xyz_float_input_boxes(engine,
		engine->object_being_placed.object->position,
		&engine->gui.float_input_boxes.position);
	if (recalculate_bvh_scene(&engine->scene,
			engine->object_being_placed.object) < 0)
		ft_fatal_error("update_placed_object_position: recalculate_bvh_scene "
			"failed");
}

static void	update_light_position(t_engine *engine, const t_vector3f direction)
{
	light_set_position(engine->object_being_placed.light, vector3f_add(
			engine->camera.position,
			vector3f_multiply(direction,
				engine->object_being_placed_distance)));
	update_xyz_float_input_boxes(engine,
		engine->object_being_placed.light->position,
		&engine->gui.float_input_boxes.position);
}

static void	update_mouse_position(t_engine *engine, t_vector2i *mouse_position)
{
	if (mouse_position->x < engine->ray_traced_image.width
		&& mouse_position->y < engine->ray_traced_image.height
		&& mouse_position->x >= 0 && mouse_position->y >= 0)
		return ;
	if (mouse_position->x >= engine->ray_traced_image.width)
		mouse_position->x %= engine->ray_traced_image.width;
	while (mouse_position->x < 0)
		mouse_position->x += engine->ray_traced_image.width;
	if (mouse_position->y >= engine->ray_traced_image.height)
		mouse_position->y %= engine->ray_traced_image.height;
	while (mouse_position->y < 0)
		mouse_position->y += engine->ray_traced_image.height;
	mouse_move(engine, *mouse_position);
}
