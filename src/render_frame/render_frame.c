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

#include "mlx.h"
#include "libft.h"

#include "engine.h"
#include "gui/box.h"
#include "render_frame.h"
#include "ray_tracer/render.h"
#include "gui/utils.h"

static void	render_minirt(t_engine *minirt);
static void	update_placed_object_position(t_engine *engine);
static void	update_mouse_position(t_engine *engine, t_vector2i *mouse_position);

int	render_frame(t_engine *minirt)
{
	const struct timeval	start_time = get_current_time();

	render_minirt(minirt);
	print_fps_counter(minirt, start_time);
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
	if (!engine->camera.lock)
	{
		t_vector2i mouse_position = get_mouse_position(engine);

		int x = engine->previous_mouse_position.x - mouse_position.x;
		int y = engine->previous_mouse_position.y - mouse_position.y;
		if (x || y)
		{
			camera_rotate_up(&engine->camera, y / 2);
			camera_rotate_left(&engine->camera, x / 2);
			camera_recalculate_view(&engine->camera);
			camera_recalculate_rays(&engine->camera);
//			ft_printf("x: %d y: %d\n", mouse_position.x, mouse_position.y);
		}
		engine->previous_mouse_position = mouse_position;
	}
	update_placed_object_position(engine);
	render_raytracing(engine);
	mlx_put_image_to_window(engine->window.mlx, engine->window.window,
		engine->ray_traced_image.data, 0, 0);
	render_user_interface(engine);
}
#else
# error "Unsuported OS"
#endif

static void	update_placed_object_position(t_engine *engine)
{
	t_vector2i	mouse_position;
	size_t		ray_index;
	t_vector3f	direction;

	if (engine->object_being_placed == NULL)
		return ;
	mouse_position = get_mouse_position(engine);
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
