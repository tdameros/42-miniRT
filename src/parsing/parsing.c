/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:18:51 by vfries            #+#    #+#             */
/*   Updated: 2023/09/25 22:12:28 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "libft.h"

#include "engine.h"
#include "parsing.h"
#include "gui/object_list_box.h"

static int	create_bvh_tree(t_engine *engine);

int	parse_scene(t_engine *engine, const char *start_up_scene)
{
	const int	fd = open(start_up_scene, O_RDONLY);
	char		***scene_content;

	if (fd == -1)
	{
		perror("Error\nFailed to open .rt file");
		return (-1);
	}
	scene_content = get_scene_content(fd);
	close(fd);
	if (scene_content == NULL)
		return (perror("Error\nFailed to init scene_content from .rt file"), \
				-1);
	if (parse_scene_content(engine, scene_content))
		return (ft_putstr_fd("Failed to parse scene_content\n", STDERR_FILENO), \
				free_scene_content(scene_content), \
				-1);
	if (create_bvh_tree(engine) < 0)
		return (free_scene_content(scene_content), \
				-1);
	update_object_list_icons(engine);
	free_scene_content(scene_content);
	return (0);
}

static int	create_bvh_tree(t_engine *engine)
{
	if (engine->scene.bvh_tree != NULL)
		return (0);
	engine->scene.bvh_tree = objects_bvh_create_tree(&engine->scene.objects);
	if (engine->scene.bvh_tree == NULL)
		return (-1);
	return (0);
}
