/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:42:56 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/23 22:42:59 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "ray_tracer/bvh.h"

void	free_scene(t_scene *scene)
{
	free_objects(&scene->objects);
	free_lights(&scene->lights);
	free_light(&scene->ambient_light);
	objects_bvh_free_tree(scene->bvh_tree);
	vectors_int_free(&scene->plane_indexes);
	ft_bzero(scene, sizeof(*scene));
}
