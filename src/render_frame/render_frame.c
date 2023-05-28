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
static void	render_raytracing(t_engine *engine);

int	render_frame(t_engine *minirt)
{
//	const struct timeval	start_time = get_current_time();

	render_minirt(minirt);
//	print_fps_counter(minirt, start_time);
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

#include "stdio.h"
void	render_raytracing(t_engine *engine)
{
	t_vector3f	color = {.x = rand() % 255, .y = rand() % 255, .z = rand() % 255};

	if (clSetKernelArg(engine->raytracing_kernel, 0, sizeof(cl_mem), &engine->ray_traced_image_gpu_buffer) != CL_SUCCESS)
		ft_print_error("clSetKernelArg 0 failed\n");
	if (clSetKernelArg(engine->raytracing_kernel, 1, sizeof(t_vector3f), &color) != CL_SUCCESS)
		ft_print_error("clSetKernelArg 1 failed\n");

	size_t	global_work_size = engine->ray_traced_image.size;
	clEnqueueNDRangeKernel(engine->opencl.commandQueue, engine->raytracing_kernel, 1, NULL, &global_work_size, NULL, 0, NULL, NULL);


	clEnqueueReadBuffer(engine->opencl.commandQueue, engine->ray_traced_image_gpu_buffer, CL_FALSE, 0, engine->ray_traced_image.size * sizeof(*engine->ray_traced_image.address), engine->ray_traced_image.address, 0, NULL, NULL);

	clFinish(engine->opencl.commandQueue);

//	t_image			*img_ptr = &engine->ray_traced_image;
//	t_scene			scene;
//	t_objects		objects;
//	t_object		object;
//
//	// TODO: dont regenerate scene every frame
//	initialize_objects_array(&objects, 10);
//	object = sphere_create(vector3f_create(0, 0, 0), 0.5,
//						   vector3f_create(1, 0, 1));
//	add_object_in_objects(&objects, object);
//	object = sphere_create(vector3f_create(-2, 0, 0), 0.5,
//						   vector3f_create(0, 1, 1));
//	add_object_in_objects(&objects, object);
//	scene.objects = objects;
//	for (int y = 0; y < img_ptr->height; y++)
//	{
//		for (int x = 0; x < img_ptr->width; x++)
//		{
//			t_ray ray = engine->camera.rays[x + y * (int) engine->camera.viewport.x];
//			t_vector3f pixel_color = render_pixel(ray, &scene);
//			pixel_color = vector3f_clamp(pixel_color, 0, 1);
//			pixel_color = vector3f_multiply(pixel_color, 255);
//			put_pixel_on_image(img_ptr, img_ptr->height - y - 1, x, vec_rgb_to_uint(pixel_color));
//		}
//	}
//	free_objects(&objects);
}
