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

#include <sys/time.h>
#include <math.h>

#include "mlx.h"
#include "libft.h"

#include "engine.h"
#include "render_frame.h"
#include "ray_tracer/render.h"
#include "gui/utils.h"
#include "font/render.h"
#include "events.h"
#include "hooks.h"
#include "mlx_wrapper.h"
#include "object.h"
#include "interpolater.h"

#define FPS_GOAL 45.f
#define FRAME_BEFORE_ADAPTION 20
#define DEFAULT_INCREMENTER_VALUE 2

#ifdef __linux__
# define IS_LINUX true
#else
# define IS_LINUX false
#endif

static void			render_screen_shot_animation(t_engine *engine);
static void			render_minirt(t_engine *engine, uint64_t start_time);
static int			adjust_incrementer(t_quality quality, int incrementer);
static int			get_incrementer(t_engine *engine);
static void			update_scene(t_engine *engine, const uint64_t start_time);
static int			deal_mouse(t_engine *engine);
static void			deal_keys(t_engine *engine, const uint64_t start_time);
static void			update_placed_object_position(t_engine *engine);
static void			update_mouse_position(t_engine *engine,
						t_vector2i *mouse_position);

int	render_frame(t_engine *engine)
{
	const struct timeval	start_time = ft_get_current_time();

	render_minirt(engine, ft_timeval_to_ms(start_time));
	render_screen_shot_animation(engine);
	if (IS_LINUX)
		mlx_put_image_to_window(engine->window.mlx, engine->window.window,
			engine->main_image.data, 0, 0);
	if (engine->should_render_ray_tracing)
		print_fps_counter(engine, start_time);
	engine->last_frame_start_time = ft_timeval_to_ms(start_time);
	return (0);
}

#define SCREEN_SHOT_ANIMATION_DURATION 250.f
static void	render_screen_shot_animation(t_engine *engine)
{
	const uint64_t	current_time = ft_get_current_time_in_ms();
	const float		time_elapsed = current_time
		- engine->gui.screen_shot.last_screen_shot;
	int16_t			transparency;

	if (time_elapsed > SCREEN_SHOT_ANIMATION_DURATION)
		return ;
	if (time_elapsed < SCREEN_SHOT_ANIMATION_DURATION / 2.f)
		transparency = roundf((1.f - time_elapsed
			/ (SCREEN_SHOT_ANIMATION_DURATION / 2.f)) * 255.f);
	else
		transparency = roundf(
				(time_elapsed - SCREEN_SHOT_ANIMATION_DURATION / 2.f)
				/ (SCREEN_SHOT_ANIMATION_DURATION / 2.f) * 255.f);
	transparency = ft_clamp(transparency, 0, 255);
	change_image_color(&engine->gui.screen_shot.image,
		COLOR_WHITE | (transparency << 24));
	put_image(engine, &engine->gui.screen_shot.image, (t_vector2i){0, 0});
}

static void	render_minirt(t_engine *engine, const uint64_t start_time)
{
	int	incrementer;

	update_scene(engine, start_time);
	if (engine->should_render_ray_tracing
		&& engine->should_render_at_full_resolution == false)
	{
		incrementer = get_incrementer(engine);
		render_raytracing(engine, incrementer);
		if (incrementer > 1)
			interpolate_ray_tracing(&engine->raytraced_pixels, incrementer);

		for (size_t i = 0; i < engine->ray_traced_image.size; i++)
			engine->ray_traced_image.address[i]
				= vec_rgb_to_uint(engine->raytraced_pixels.data[i]);
		engine->scene_changed = false;
	}
	else if (engine->should_render_ray_tracing
		&& engine->should_render_at_full_resolution)
	{
		if (engine->antialiasing)
			render_anti_aliased_raytracing(engine);
		else
		{
			render_raytracing(engine, engine->quality.min_reduction);
			if (engine->quality.min_reduction > 1)
				interpolate_ray_tracing(&engine->raytraced_pixels,
					engine->quality.min_reduction);
		}
		for (size_t i = 0; i < engine->ray_traced_image.size; i++)
			engine->ray_traced_image.address[i]
					= vec_rgb_to_uint(engine->raytraced_pixels.data[i]);
		engine->scene_changed = false;
	}
	put_image(engine, &engine->ray_traced_image, (t_vector2i){0, 0});
	render_bounding_box(engine);
	put_image(engine, &engine->bvh_image, (t_vector2i){0, 0});
	render_user_interface(engine, start_time);
}

static int	get_incrementer(t_engine *engine)
{
	static int	incrementer = DEFAULT_INCREMENTER_VALUE;
	static int	fps_count = 0;
	static int	frame_count = 0;
	float		average_fps;

	if (engine->should_render_at_full_resolution)
		return (engine->quality.min_reduction);
	fps_count += engine->gui.fps.fps_nb;
	frame_count++;
	if (frame_count >= FRAME_BEFORE_ADAPTION)
	{
		average_fps = fps_count / (float)frame_count;
		if (average_fps <= FPS_GOAL * 0.66f)
			incrementer++;
		else if (incrementer > 1 && average_fps > FPS_GOAL * 1.33f)
			incrementer--;
		frame_count = 0;
		fps_count = 0;
	}
	incrementer = adjust_incrementer(engine->quality, incrementer);
	return (incrementer);
}

static int	adjust_incrementer(t_quality quality, int incrementer)
{
	if (incrementer >= quality.max_reduction)
		return (quality.max_reduction);
	if (incrementer <= quality.min_reduction)
		return (quality.min_reduction);
	return (incrementer);
}

#define NB_OF_MS_BEFORE_FULL_RESOLUTION 600

static void	update_scene(t_engine *engine, const uint64_t start_time)
{
	static uint64_t			next_update_time = 0;
	static bool				was_rendered_at_full_resolution = false;
	const uint64_t			current_time_in_ms = ft_timeval_to_ms(
			ft_get_current_time());

	deal_keys(engine, start_time);
	if (deal_mouse(engine) || engine->pressed_keys_index > 0)
	{
		camera_recalculate_view(&engine->camera);
		camera_recalculate_rays(&engine->camera);
		engine->should_render_ray_tracing = true;
		engine->should_render_at_full_resolution = false;
		was_rendered_at_full_resolution = false;
		next_update_time = current_time_in_ms + NB_OF_MS_BEFORE_FULL_RESOLUTION;
		engine->scene_changed = true;
		update_placed_object_position(engine);
		return ;
	}
	update_placed_object_position(engine);
	if (engine->scene_changed)
	{
		engine->should_render_ray_tracing = true;
		engine->should_render_at_full_resolution = false;
		was_rendered_at_full_resolution = false;
		next_update_time = current_time_in_ms + NB_OF_MS_BEFORE_FULL_RESOLUTION;
	}
	else if (current_time_in_ms >= next_update_time)
	{
		if (was_rendered_at_full_resolution)
			engine->should_render_ray_tracing = false;
		else if (engine->gui.hide_animation.hide_animation_finished)
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
		mouse_move(engine, (t_vector2i){engine->ray_traced_image.width / 2,
			engine->ray_traced_image.height / 2});
		engine->previous_mouse_position = (t_vector2i){
			engine->window.size.x / 2, engine->window.size.y / 2};
		return (1);
	}
	return (0);
}

#define TIME_FOR_FULL_DEFAULT_MOVEMENT_MS 25
#define DEFAULT_MOUVEMENT 0.4f

static void	deal_keys(t_engine *engine, const uint64_t start_time)
{
	const float	time_since_last_frame = start_time
										   - engine->last_frame_start_time;
	const float	movement_ratio = time_since_last_frame
									/ TIME_FOR_FULL_DEFAULT_MOVEMENT_MS;
	const float	movement = DEFAULT_MOUVEMENT * movement_ratio;
	int			i;

	i = -1;
	while (++i < engine->pressed_keys_index)
	{
		if (engine->pressed_keys[i] == KEY_W)
			camera_move_forward(&engine->camera, movement);
		else if (engine->pressed_keys[i] == KEY_S)
			camera_move_forward(&engine->camera, -movement);
		else if (engine->pressed_keys[i] == KEY_A)
			camera_move_left(&engine->camera, movement);
		else if (engine->pressed_keys[i] == KEY_D)
			camera_move_left(&engine->camera, -movement);
		else if (engine->pressed_keys[i] == KEY_SPACE)
			camera_move_up(&engine->camera, movement);
		else if (engine->pressed_keys[i] == KEY_L_SHIFT)
			camera_move_up(&engine->camera, -movement);
		else if (engine->pressed_keys[i] == KEY_Q)
			camera_peek(&engine->camera, -movement * 10.f);
		else if (engine->pressed_keys[i] == KEY_E)
			camera_peek(&engine->camera, movement * 10.f);
	}
}


static void	update_placed_object_position(t_engine *engine)
{
	t_vector2i	mouse_position;
	size_t		ray_index;
	t_vector3f	direction;
	float		yaw_delta;
	float		pitch_delta;

	if (engine->object_being_placed.object == NULL
		&& engine->object_being_placed.light == NULL)
		return ;
	mouse_position = get_mouse_position(engine);
	yaw_delta = (engine->previous_mouse_position.x - mouse_position.x)
		* engine->camera.rotation_speed;
	pitch_delta = (engine->previous_mouse_position.y - mouse_position.y)
		* engine->camera.rotation_speed;
	if (yaw_delta == 0 && pitch_delta == 0 && engine->scene_changed == false)
		return ;
	engine->scene_changed = true;
	update_mouse_position(engine, &mouse_position);
	engine->previous_mouse_position = mouse_position;
	ray_index = mouse_position.x + mouse_position.y \
			* (int)engine->camera.viewport.size.x;
	direction = engine->camera.rays[ray_index].direction;
	if (engine->object_being_placed.object != NULL)
	{
		object_set_position(engine->object_being_placed.object, vector3f_add(
				engine->camera.position,
				vector3f_multiply(direction,
					engine->object_being_placed_distance)));
		update_xyz_float_input_boxes(engine,
			engine->object_being_placed.object->position,
			&engine->gui.float_input_boxes.position);
		if (recalculate_bvh_scene(&engine->scene, engine->object_being_placed.object) < 0)
			ft_fatal_error("update_placed_object_position: recalculate_bvh_scene failed");
	}
	else
	{
		light_set_position(engine->object_being_placed.light, vector3f_add(
				engine->camera.position,
				vector3f_multiply(direction,
					engine->object_being_placed_distance)));
		update_xyz_float_input_boxes(engine,
			engine->object_being_placed.light->position,
			&engine->gui.float_input_boxes.position);
	}
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
