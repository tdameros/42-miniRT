/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_and_remove_object_and_light.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:44:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/18 21:44:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gui/box.h"
#include "gui/object_list_box.h"

static int	update_plane_indexes(t_scene *scene);

int	add_object(t_engine *engine, const t_object object)
{
	t_gui_box	gui_box;

	if (add_object_in_objects(&engine->scene.objects, object) < 0)
		return (ft_print_error("Failed to add new object\n"), -1);
	if (object.type == PLANE)
	{
		if (vectors_int_add(&engine->scene.plane_indexes,
				engine->scene.objects.length - 1) < 0)
			return (ft_print_error("Failed to add new object\n"), -1);
	}
	if (recalculate_bvh_scene(&engine->scene,
			&engine->scene.objects.data[engine->scene.objects.length - 1]) < 0)
		ft_fatal_error("add_object: recalculate_bvh_scene failed");
	create_object_gui_box(engine, &gui_box, &object);
	if (ft_vector_add_elem(&engine->gui.object_boxes, &gui_box) < 0)
		ft_fatal_error("add_object: ft_vector_add_elem failed");
	return (0);
}

int	add_light(t_engine *engine, const t_light light)
{
	t_gui_box	gui_box;

	if (add_light_in_lights(&engine->scene.lights, light) < 0)
		return (ft_print_error("Failed to add new light\n"), -1);
	create_light_gui_box(engine, &gui_box, &light);
	if (ft_vector_add_elem(&engine->gui.light_boxes, &gui_box) < 0)
		ft_fatal_error("add_light: ft_vector_add_elem failed");
	return (0);
}

void	remove_object(t_engine *engine, const size_t index)
{
	if (index >= engine->scene.objects.length)
		return ;
	destroy_t_gui_box(&engine->window,
		((t_gui_box *)engine->gui.object_boxes.data) + index);
	ft_vector_delete_elem(&engine->gui.object_boxes, index, false);
	remove_object_in_objects(&engine->scene.objects, index);
	update_plane_indexes(&engine->scene);
	if (recalculate_bvh_scene(&engine->scene, NULL) < 0)
		ft_fatal_error("add_object: recalculate_bvh_scene failed");
}

void	remove_light(t_engine *engine, const size_t index)
{
	if (index >= engine->scene.lights.length)
		return ;
	destroy_t_gui_box(&engine->window,
		((t_gui_box *)engine->gui.light_boxes.data) + index);
	ft_vector_delete_elem(&engine->gui.light_boxes, index, false);
	remove_light_in_lights(&engine->scene.lights, index);
}

static int	update_plane_indexes(t_scene *scene)
{
	size_t	i;
	int		return_code;

	i = 0;
	vectors_int_free(&scene->plane_indexes);
	vectors_int_initialize(&scene->plane_indexes, 5);
	return_code = 0;
	while (i < scene->objects.length)
	{
		if (scene->objects.data[i].type == PLANE)
			return_code = vectors_int_add(&scene->plane_indexes, i);
		if (return_code < 0)
		{
			vectors_int_free(&scene->plane_indexes);
			return (-1);
		}
		i++;
	}
	return (0);
}
