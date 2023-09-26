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

static int	update_plane_indexes(t_scene *scene);

int	add_object(t_engine *engine, const t_object object)
{
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
	return (0);
}

int	add_light(t_engine *engine, const t_light light)
{
	if (add_light_in_lights(&engine->scene.lights, light) < 0)
		return (ft_print_error("Failed to add new light\n"), -1);
	return (0);
}

void	remove_object(t_engine *engine, const size_t index)
{
	if (index >= engine->scene.objects.length)
		return ;
	remove_object_in_objects(&engine->scene.objects, index);
	update_plane_indexes(&engine->scene);
	if (recalculate_bvh_scene(&engine->scene, NULL) < 0)
		ft_fatal_error("add_object: recalculate_bvh_scene failed");
}

void	remove_light(t_engine *engine, const size_t index)
{
	if (index >= engine->scene.lights.length)
		return ;
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
