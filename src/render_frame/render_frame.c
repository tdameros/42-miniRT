/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:12:50 by vfries            #+#    #+#             */
/*   Updated: 2023/05/07 18:38:22 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <limits.h>

#include "mlx.h"
#include "libft.h"

#include "engine.h"
#include "gui/box.h"
#include "render_frame.h"
#include "ray_tracer/render.h"
#include "gui/utils.h"
#include "font/render.h"
#include "events.h"

#define FPS_GOAL 45
#define FRAME_BEFORE_ADAPTION 20

static void			render_minirt(t_engine *engine);
static int			get_incrementer(t_engine *engine);
static void			update_camera(t_engine *engine);
static int			deal_mouse(t_engine *engine);
static void			deal_keys(t_engine *engine);
static void			update_placed_object_position(t_engine *engine);
static void			update_mouse_position(t_engine *engine,
						t_vector2i *mouse_position);

int	render_frame(t_engine *engine)
{
	const struct timeval	start_time = ft_get_current_time();

	render_minirt(engine);
	if (engine->should_render_ray_tracing)
		print_fps_counter(engine, start_time);
	return (0);
}

#if defined __linux__

static void	render_minirt(t_engine *minirt)
{
	render_raytracing(minirt);
	if (minirt->gui.is_hidden && minirt->gui.hidden_ratio == 1.0)
		mlx_put_image_to_window(minirt->window.mlx, minirt->window.window,
								minirt->ray_traced_image.data, 0, 0);
	else
	{
		put_background(&minirt->main_image, &minirt->ray_traced_image);
		render_user_interface(minirt);
		mlx_put_image_to_window(minirt->window.mlx, minirt->window.window,
			minirt->main_image.data, 0, 0);
	}
}
#elif defined __APPLE__

static void	render_minirt(t_engine *engine)
{
	int	incrementer;

	update_camera(engine);
	update_placed_object_position(engine);
	if (engine->should_render_ray_tracing
		&& engine->should_render_at_full_resolution == false)
	{
		incrementer = get_incrementer(engine);
		render_raytracing(engine, incrementer);
		if (incrementer > 1)
			interpolate_ray_tracing(&engine->raytraced_pixels, incrementer);
		for (size_t i = 0; i < engine->ray_traced_image.size; i++)
			engine->ray_traced_image.address[i] = vec_rgb_to_uint(engine->raytraced_pixels.data[i]);
		engine->scene_changed = false;
	}
	else if (engine->should_render_ray_tracing
		&& engine->should_render_at_full_resolution)
	{
		render_anti_aliased_raytracing(engine);
		engine->scene_changed = false;
	}
	mlx_put_image_to_window(engine->window.mlx, engine->window.window,
		engine->ray_traced_image.data, 0, 0);
	render_user_interface(engine);
}
#else
# error "Unsuported OS"
#endif

static int	get_incrementer(t_engine *engine)
{
	static int	incrementer = 2;
	static int	fps_count = 0;
	static int	frame_count = 0;

	if (engine->should_render_at_full_resolution)
		return (1);
	fps_count += engine->gui.fps.fps_nb;
	if (frame_count >= FRAME_BEFORE_ADAPTION
		&& fps_count / frame_count < FPS_GOAL)// * 0.66f)
	{
		incrementer++;
		frame_count = 0;
		fps_count = 0;
		return (incrementer);
	}
	if (frame_count >= FRAME_BEFORE_ADAPTION && incrementer > 1
		&& fps_count / frame_count > FPS_GOAL * 1.33f)
	{
		incrementer--;
		frame_count = 0;
		fps_count = 0;
		return (incrementer);
	}
	frame_count++;
	return (incrementer);
}

#define NB_OF_MS_BEFORE_FULL_RESOLUTION 400

static void	update_camera(t_engine *engine)
{
	static long long		next_update_time = LLONG_MIN;
	static bool				was_rendered_at_full_resolution = false;
	const struct timeval	current_time = ft_get_current_time();
	const long long			current_time_in_ms
		= ft_convert_timeval_to_ms(current_time);

	deal_keys(engine);
	if (deal_mouse(engine) || engine->pressed_keys_index > 0)
	{
		camera_recalculate_view(&engine->camera);
		camera_recalculate_rays(&engine->camera);
		engine->should_render_at_full_resolution = false;
		engine->should_render_ray_tracing = true;
		was_rendered_at_full_resolution = false;
		next_update_time = current_time_in_ms + NB_OF_MS_BEFORE_FULL_RESOLUTION;
		engine->scene_changed = true;
	}
	else if (engine->scene_changed)
	{
		engine->should_render_at_full_resolution = true;
		engine->should_render_ray_tracing = true;
		was_rendered_at_full_resolution = false;
		next_update_time = current_time_in_ms + NB_OF_MS_BEFORE_FULL_RESOLUTION;
	}
	else if (current_time_in_ms >= next_update_time)
	{
		if (was_rendered_at_full_resolution)
			engine->should_render_ray_tracing = false;
		else
		{
			engine->should_render_at_full_resolution = true;
			was_rendered_at_full_resolution = true;
		}
	}
}

static int	deal_mouse(t_engine *engine)
{
	t_vector2i	mouse_position;
	float		yaw_delta;
	float		pitch_delta;

	if (engine->camera.lock == false)
	{
		mouse_position = get_mouse_position(engine);

		yaw_delta = (engine->previous_mouse_position.x - mouse_position.x)
			* engine->camera.rotation_speed;
		pitch_delta = (engine->previous_mouse_position.y - mouse_position.y)
			* engine->camera.rotation_speed;
		if (yaw_delta != 0 || pitch_delta != 0)
		{
			camera_rotate_up(&engine->camera, pitch_delta);
			camera_rotate_left(&engine->camera, yaw_delta);
		}
		else
			return (0);
		mlx_mouse_move(engine->window.window,
			engine->ray_traced_image.width / 2,
			engine->ray_traced_image.height / 2);
		engine->previous_mouse_position = (t_vector2i){
			engine->window.size.x / 2, engine->window.size.y / 2};
		return (1);
	}
	return (0);
}

static void	deal_keys(t_engine *engine)
{
	int	i;

	i = -1;
	while (++i < engine->pressed_keys_index)
	{
		if (engine->pressed_keys[i] == KEY_W)
			camera_move_forward(&engine->camera, 0.4f);
		else if (engine->pressed_keys[i] == KEY_S)
			camera_move_forward(&engine->camera, -0.4f);
		else if (engine->pressed_keys[i] == KEY_A)
			camera_move_left(&engine->camera, 0.4f);
		else if (engine->pressed_keys[i] == KEY_D)
			camera_move_left(&engine->camera, -0.4f);
		else if (engine->pressed_keys[i] == KEY_SPACE)
			camera_move_up(&engine->camera, 0.4f);
		else if (engine->pressed_keys[i] == KEY_L_SHIFT)
			camera_move_up(&engine->camera, -0.4f);
		else if (engine->pressed_keys[i] == KEY_Q)
			camera_peek(&engine->camera, 4.f);
		else if (engine->pressed_keys[i] == KEY_E)
			camera_peek(&engine->camera, -4.f);
	}
}

//static t_vector2i	clamp_mouse(t_engine *engine, t_vector2i mouse_position)
//{
//	if (mouse_position.x < 0)
//		mouse_position.x = engine->camera.viewport.size.x - 1;
//	else if (mouse_position.x >= engine->camera.viewport.size.x - 1)
//		mouse_position.x = 0;
//	if (mouse_position.y < 0)
//		mouse_position.y = engine->camera.viewport.size.y - 1;
//	else if (mouse_position.y >= engine->camera.viewport.size.y - 1)
//		mouse_position.y = 0;
//	mlx_mouse_move(engine->window.window,
//		mouse_position.x,
//		mouse_position.y);
//	return (mouse_position);
//}

static void	update_placed_object_position(t_engine *engine)
{
	t_vector2i	mouse_position;
	size_t		ray_index;
	t_vector3f	direction;
	float		yaw_delta;
	float		pitch_delta;

	if (engine->object_being_placed == NULL)
		return ;
	mouse_position = get_mouse_position(engine);
	yaw_delta = (engine->previous_mouse_position.x - mouse_position.x)
		* engine->camera.rotation_speed;
	pitch_delta = (engine->previous_mouse_position.y - mouse_position.y)
		* engine->camera.rotation_speed;
	if (yaw_delta == 0 && pitch_delta == 0 && engine->scene_changed == false)
		return ;
	engine->scene_changed = true;
	engine->previous_mouse_position = mouse_position;
	update_mouse_position(engine, &mouse_position);
	ray_index = mouse_position.x + mouse_position.y \
			* (int)engine->camera.viewport.size.x;
	direction = engine->camera.rays[ray_index].direction;
	engine->object_being_placed->position = (t_vector3f){
		.x = engine->camera.position.x + engine->object_being_placed_distance \
			* direction.x,
		.y = engine->camera.position.y + engine->object_being_placed_distance \
			* direction.y,
		.z = engine->camera.position.z + engine->object_being_placed_distance \
			* direction.z
	};
}

static void	update_mouse_position(t_engine *engine, t_vector2i *mouse_position)
{
	bool	should_update_mouse_position;

	should_update_mouse_position = (
			mouse_position->x >= engine->camera.viewport.size.x
			|| mouse_position->y >= engine->camera.viewport.size.y
			|| mouse_position->x < 0 || mouse_position->y < 0);
	if (should_update_mouse_position == false)
		return ;
	while (mouse_position->x >= engine->camera.viewport.size.x)
		mouse_position->x -= engine->camera.viewport.size.x;
	while (mouse_position->x < 0)
		mouse_position->x += engine->camera.viewport.size.x;
	while (mouse_position->y >= engine->camera.viewport.size.y)
		mouse_position->y -= engine->camera.viewport.size.y;
	while (mouse_position->y < 0)
		mouse_position->y += engine->camera.viewport.size.y;
	mlx_mouse_move(engine->window.window, mouse_position->x, mouse_position->y);
}
