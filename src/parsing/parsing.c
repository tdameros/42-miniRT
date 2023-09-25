/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:18:51 by vfries            #+#    #+#             */
/*   Updated: 2023/09/24 03:46:56 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "libft.h"

#include "engine.h"
#include "parsing.h"
#include "gui/object_list_box.h"

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
	engine->scene.bvh_tree = objects_bvh_create_tree(&engine->scene.objects);
	if (engine->scene.bvh_tree == NULL)
		return (free_scene_content(scene_content), \
				-1);
	update_object_list_icons(engine);
	free_scene_content(scene_content);
	return (0);
}
