/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_icon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 01:03:00 by vfries            #+#    #+#             */
/*   Updated: 2023/09/24 01:05:06 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "engine.h"
#include "ray_tracer/render.h"
#include "ray_tracer_gui_api.h"
#include "gui/utils.h"

static void			tmp_camera_create(t_camera *camera, t_vector2f viewport);
static void			init_tmp_scene(t_engine *tmp_engine, const t_object *object,
						t_vector3f sky_color);

void	draw_icon(t_image *image, const t_object *object, const t_light *light,
			const unsigned int background_color)
{
	t_engine		tmp_engine;
	const t_color	sky_color = vector3f_divide(
			get_t_color_from_uint(background_color), 255.f);

	if (light != NULL)
		return (draw_light_icon(image, background_color, light->color));
	if (object == NULL)
		return ;
	ft_bzero(&tmp_engine, sizeof(tmp_engine));
	tmp_engine.ray_traced_image = *image;
	tmp_camera_create(&tmp_engine.camera,
		(t_vector2f){image->width, image->height});
	init_tmp_scene(&tmp_engine, object, sky_color);
	if (recalculate_bvh_scene(&tmp_engine.scene, tmp_engine.scene.objects.data)
		< 0)
		ft_fatal_error("recalculate_bvh_scene() failed while drawing icon");
	render_icon(&tmp_engine, background_color);
	free_scene(&tmp_engine.scene);
	camera_free(&tmp_engine.camera);
}

static void	tmp_camera_create(t_camera *camera, t_vector2f viewport)
{
	camera->viewport.number_of_pixels = viewport.x * viewport.y;
	camera->viewport.size = viewport;
	camera->position = vector3f_create(0, 0, 0);
	camera->direction = vector3f_create(0, 0, -1);
	camera->up_vector = vector3f_create(0, 1, 0);
	camera->view = matrix4_create_identity();
	camera->inverse_view = matrix4_create_identity();
	camera->projection = matrix4_create_identity();
	camera->inverse_projection = matrix4_create_identity();
	camera->horizontal_fov = 45.f;
	camera->near_clip = 0.1f;
	camera->far_clip = 100;
	camera->pitch = 0;
	camera->rotation_speed = 0.3f;
	camera->lock = true;
	camera_recalculate_view(camera);
	camera_recalculate_projection(camera);
}

static void	init_tmp_scene(t_engine *tmp_engine, const t_object *base_object,
				const t_vector3f sky_color)
{
	t_object	object;
	t_light		light;

	if (initialize_objects_array(&tmp_engine->scene.objects, 1) < 0
		|| initialize_lights_array(&tmp_engine->scene.lights, 1) < 0)
		ft_fatal_error("Failed to init object and light array in draw_icon()");
	object = get_object(base_object, tmp_engine);
	light = light_create(vector3f_create(5, 5, 5), vector3f_create(1, 1, 1),
			1.f);
	if (add_object_in_objects(&tmp_engine->scene.objects, object) < 0
		|| add_light_in_lights(&tmp_engine->scene.lights, light) < 0)
		ft_fatal_error("Failed to add light and object to list during "
			"draw_icon()");
	if (object.type == PLANE)
	{
		vectors_int_initialize(&tmp_engine->scene.plane_indexes, 1);
		vectors_int_add(&tmp_engine->scene.plane_indexes,
			tmp_engine->scene.objects.length - 1);
	}
	tmp_engine->scene.sky_color = sky_color;
	tmp_engine->scene.ambient_light.color = vector3f_create(1, 1, 1);
	tmp_engine->scene.ambient_light.brightness = 0.2f;
}
