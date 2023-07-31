/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:18:55 by vfries            #+#    #+#             */
/*   Updated: 2023/04/21 03:22:28 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#include "libft.h"

#include "engine.h"
#include "parsing.h"

static int	parse_scene_content_line(t_engine *minirt,
									   char **scene_content_line,
									   t_rt_file_requirements *rt_file_requirements,
									   t_list **object_list);
static int	get_function_index(char *scene_content_line);
static int	put_object_list_in_minirt(t_objects *objects, t_list *object_list);

int	parse_scene_content(t_engine *minirt, char ***scene_content)
{
	size_t					i;
	t_rt_file_requirements	rt_file_requirements;
	t_list					*object_list;

	ft_bzero(&rt_file_requirements, sizeof(t_rt_file_requirements));
	minirt->raytracing_data.camera.horizontal_fov = 90;
	object_list = NULL;
	i = 0;
	while (scene_content[i] != NULL)
	{
		errno = 0;
		if (parse_scene_content_line(minirt, scene_content[i],
				&rt_file_requirements, &object_list) < 0)
		{
			ft_putstr_fd("Failed to parse scene_content line\n", STDERR_FILENO);
			if (errno != 0)
				perror("errno value");
			return (-1);
		}
		i++;
	}
	return (put_object_list_in_minirt(&minirt->raytracing_data.objects,
			object_list));
}

static int	parse_scene_content_line(t_engine *minirt,
									   char **scene_content_line,
									   t_rt_file_requirements *rt_file_requirements,
									   t_list **object_list)
{
	int			(*parse_line[6])(t_engine *, char **, t_rt_file_requirements *,
									t_list **);
	const int	function_index = get_function_index(scene_content_line[0]);

	parse_line[0] = &parse_ambient_light;
	parse_line[1] = &parse_camera;
	parse_line[2] = &parse_light;
	parse_line[3] = &parse_sphere;
	parse_line[4] = &parse_plane;
	parse_line[5] = &parse_cylinder;
	if (function_index < 0)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		invalid_scene_content_line(scene_content_line);
		return (-1);
	}
	if (parse_line[function_index](minirt, scene_content_line,
		rt_file_requirements, object_list) < 0)
	{
		invalid_scene_content_line(scene_content_line);
		return (-1);
	}
	return (0);
}

static int	get_function_index(char *scene_content_line)
{
	const char	*function_name[] = {
		"A",
		"C",
		"L",
		"sp",
		"pl",
		"cy",
	};
	int			i;

	i = 0;
	while (i < (int)(sizeof(function_name) / sizeof(char *)))
	{
		if (ft_strcmp(scene_content_line, function_name[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	put_object_list_in_minirt(t_objects *objects, t_list *object_list)
{
	size_t	i;

	objects->length = ft_lstsize(object_list);
	objects->size = objects->length * 2;
	objects->data = ft_calloc(objects->size, sizeof(*objects->data));
	if (objects->data == NULL)
	{
		ft_putstr_fd("Error\nFailed to allocate memory for objects\n",
			STDERR_FILENO);
		return (-1);
	}
	i = 0;
	while (i < objects->length)
	{
		objects->data[i] = *(t_object *)object_list->content;
		ft_lst_get_next_free_current(&object_list, &free);
		i++;
	}
	return (0);
}
