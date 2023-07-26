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

int	add_object(t_engine *engine, const t_object object)
{
	t_gui_box	gui_box;

	if (add_object_in_objects(&engine->scene.objects, object) < 0)
		return (ft_print_error("Failed to add new object\n"), -1);
	if (create_object_gui_box(engine, &gui_box, &object) < 0)
	{
		remove_object_in_objects(&engine->scene.objects,
			engine->scene.objects.length - 1);
		free(object.name);
		ft_print_error("Failed to add new object\n");
		return (-1);
	}
	if (ft_vector_add_elem(&engine->gui.object_boxes, &gui_box) < 0)
	{
		remove_object_in_objects(&engine->scene.objects,
			engine->scene.objects.length - 1);
		destroy_t_gui_box(&engine->window, &gui_box);
		free(object.name);
		ft_print_error("Failed to add new object\n");
		return (-1);
	}
	return (0);
}

int	add_light(t_engine *engine, const t_light light)
{
	t_gui_box	gui_box;

	if (add_light_in_lights(&engine->scene.lights, light) < 0)
		return (ft_print_error("Failed to add new light\n"), -1);
	if (create_light_gui_box(engine, &gui_box, &light) < 0)
	{
		remove_light_in_lights(&engine->scene.lights,
			engine->scene.lights.length - 1);
		free(light.name);
		ft_print_error("Failed to add new light\n");
		return (-1);
	}
	if (ft_vector_add_elem(&engine->gui.light_boxes, &gui_box) < 0)
	{
		remove_light_in_lights(&engine->scene.lights,
			engine->scene.lights.length - 1);
		destroy_t_gui_box(&engine->window, &gui_box);
		free(light.name);
		ft_print_error("Failed to add new light\n");
		return (-1);
	}
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
