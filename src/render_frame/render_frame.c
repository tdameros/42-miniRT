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

static void	render_minirt(t_engine *minirt);
static void	render_raytracing(t_engine *minirt);

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
	draw(minirt);
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

static void	render_minirt(t_engine *minirt)
{
	render_raytracing(minirt);
	mlx_put_image_to_window(minirt->window.mlx, minirt->window.window,
		minirt->ray_traced_image.data, 0, 0);
	render_user_interface(minirt);
}
#else
# error "Unsuported OS"
#endif

void	render_raytracing(t_engine *minirt)
{
	t_image			*img_ptr = &minirt->ray_traced_image;
	t_scene			scene;
	t_objects		objects;
	t_object		object;

	// TODO: dont regenerate scene every frame
	initialize_objects_array(&objects, 10);
	object = sphere_create(vector3f_create(0, 0, 0), 0.5,
						   vector3f_create(1, 0, 1));
	add_object_in_objects(&objects, object);
	object = sphere_create(vector3f_create(-2, 0, 0), 0.5,
						   vector3f_create(0, 1, 1));
	add_object_in_objects(&objects, object);
	scene.objects = objects;
	for (int y = 0; y < img_ptr->height; y++)
	{
		for (int x = 0; x < img_ptr->width; x++)
		{
			t_ray ray = minirt->camera.rays[x + y * (int) minirt->camera.viewport.x];
			t_vector3f pixel_color = render_pixel(ray, &scene);
			pixel_color = vector3f_clamp(pixel_color, 0, 1);
			pixel_color = vector3f_multiply(pixel_color, 255);
			put_pixel_on_image(img_ptr, img_ptr->height - y - 1, x, vec_rgb_to_uint(pixel_color));
		}
	}
	free_objects(&objects);
}
