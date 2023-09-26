/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_engine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 03:07:36 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/25 22:16:23 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlx.h"
#include "libft.h"

#include "engine.h"
#include "gui/box.h"

static void	destroy_images(t_engine *engine);
static void	destroy_gui(t_engine *minirt);
static void	destroy_font(t_font *font);
static void	free_vector_of_gui_boxes(t_engine *engine, t_vector *vector);

int	close_engine(t_engine *engine)
{
	if (engine->command_key_is_pressed)
		mlx_do_key_autorepeaton(engine->window.mlx);
	destroy_gui(engine);
	destroy_images(engine);
	free_scene(&engine->scene);
	camera_free(&engine->camera);
	free(engine->start_up_scene);
	destroy_mlx(engine);
	exit(0);
}

static void	destroy_images(t_engine *engine)
{
	destroy_t_image(&engine->window, &engine->main_image);
	destroy_t_image(&engine->window, &engine->ray_traced_image);
	destroy_t_image(&engine->window, &engine->bvh_image);
	free(engine->raytraced_pixels.data);
	engine->raytraced_pixels.data = NULL;
}

static void	destroy_gui(t_engine *engine)
{
	destroy_font(&engine->gui.font);
	destroy_t_image(&engine->window, &engine->gui.screen_shot.image);
	destroy_t_gui_boxes(&engine->window, &engine->gui.gui_boxes);
	destroy_t_gui_boxes(&engine->window, &engine->gui.optional_gui_boxes);
	ft_free_split(engine->gui.color_and_material.textures_and_normal_maps.\
		textures_files);
	destroy_t_gui_boxes(&engine->window, &engine->gui.color_and_material.\
		textures_and_normal_maps.textures_boxes);
	ft_free_split(engine->gui.color_and_material.textures_and_normal_maps.\
		normal_maps_files);
	destroy_t_gui_boxes(&engine->window, &engine->gui.color_and_material.\
		textures_and_normal_maps.normal_maps_boxes);
	ft_free_split(engine->gui.mesh_objects.mesh_files);
	destroy_t_gui_boxes(&engine->window, &engine->gui.mesh_objects.mesh_boxes);
	free(engine->gui.fps.fps_count);
	free_vector_of_gui_boxes(engine, &engine->gui.object_boxes);
	free_vector_of_gui_boxes(engine, &engine->gui.light_boxes);
	destroy_t_image(&engine->window, &engine->gui.message.image_to_display);
	destroy_t_image(&engine->window, &engine->gui.message.image_with_message);
}

static void	destroy_font(t_font *font)
{
	size_t	i;

	i = NUMBER_OF_GLYPHS;
	while (i--)
	{
		free(font->glyphs[i].points);
		free(font->glyphs[i].contours_limits);
	}
	free(font->glyphs);
	free(font->long_hor_metric);
}

static void	free_vector_of_gui_boxes(t_engine *engine, t_vector *vector)
{
	size_t	i;

	i = vector->length;
	while (i--)
		destroy_t_gui_box(&engine->window,
			ft_vector_get_ptr_to_elem(vector, i));
	ft_vector_destroy(vector);
}
