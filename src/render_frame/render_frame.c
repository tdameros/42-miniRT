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

//static void	denoise_raytracing(t_engine *engine);
static void	render_minirt(t_engine *engine)
{
	update_placed_object_position(engine);
	render_raytracing(engine);

//	if (engine->frame_count > 500)
//	{
//		denoise_raytracing(engine);
//		mlx_put_image_to_window(engine->window.mlx, engine->window.window,
//								engine->denoised_ray_traced_image.data, 0, 0);
//	}
//	else
		mlx_put_image_to_window(engine->window.mlx, engine->window.window,
			engine->ray_traced_image.data, 0, 0);
	render_user_interface(engine);
}
#else
# error "Unsuported OS"
#endif

//static t_color denoise_pixel(t_image *src, int x, int y, float ratio);
//static void	denoise_raytracing(t_engine *engine)
//{
//	for (ssize_t y = engine->ray_traced_image.height - 1; y >= 0; y--)
//	{
//		for (ssize_t x = engine->ray_traced_image.width - 1; x >= 0; x--)
//			engine->denoised_ray_traced_image.address[y * engine->denoised_ray_traced_image.width + x]
//				= vec_rgb_to_uint(denoise_pixel(&engine->ray_traced_image, x, y, 1.f));
//	}
//}

//#define RATION_CHANGE 0.8f
//static t_color denoise_pixel(t_image *src, int x, int y, float ratio)
//{
//	t_color	color;
//	float	divide_nb;
//
//	if (ratio <= 0.f ||
//		x < 0 || x >= src->width
//		|| y < 0 || y >= src->height)
//		return ((t_color){0.f, 0.f, 0.f});
//	color = get_t_color_from_uint(src->address[y * src->width + x]);
//	divide_nb = ratio;
//	if (ratio - RATION_CHANGE >= 0.f)
//	{
//		if (y - 1 >= 0)
//		{
//			color = vector3f_add(color, denoise_pixel(src, y - 1, x, ratio - RATION_CHANGE));
//			divide_nb += ratio - RATION_CHANGE;
//		}
//		if (y + 1 < src->height)
//		{
//			color = vector3f_add(color, denoise_pixel(src, y + 1, x, ratio - RATION_CHANGE));
//			divide_nb += ratio - RATION_CHANGE;
//		}
//		if (x - 1 >= 0)
//		{
//			color = vector3f_add(color, denoise_pixel(src, y, x - 1, ratio - RATION_CHANGE));
//			divide_nb += ratio - RATION_CHANGE;
//		}
//		if (x + 1 < src->height)
//		{
//			color = vector3f_add(color, denoise_pixel(src, y, x + 1, ratio - RATION_CHANGE));
//			divide_nb += ratio - RATION_CHANGE;
//		}
//	}
//	return (vector3f_multiply(vector3f_divide(color, divide_nb), ratio));
//}

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
