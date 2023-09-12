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

static int	parse_scene_content_line(t_engine *engine,
				char **scene_content_line,
				t_rt_file_requirements *rt_file_requirements);
static int	get_function_index(char *scene_content_line);
static bool	are_requirements_met(t_rt_file_requirements rt_file_requirements);

int	parse_scene_content(t_engine *engine, char ***scene_content)
{
	size_t					i;
	t_rt_file_requirements	rt_file_requirements;

	ft_bzero(&rt_file_requirements, sizeof(t_rt_file_requirements));
	i = 0;
	while (scene_content[i] != NULL)
	{
		errno = 0;
		if (parse_scene_content_line(engine, scene_content[i],
				&rt_file_requirements) < 0)
		{
			ft_putstr_fd("Failed to parse scene_content line\n", STDERR_FILENO);
			if (errno != 0)
				perror("errno value");
			// TODO free engine->scene?
			return (-1);
		}
		i++;
	}
	if (!are_requirements_met(rt_file_requirements))
	{
		ft_print_error("Error\nMissing requirements in .rt file\n");
		return (-1);
	}
	return (0);
}

static int	parse_scene_content_line(t_engine *engine,
				char **scene_content_line,
				t_rt_file_requirements *rt_file_requirements)
{
	int			(*parse_line[8])(t_engine *, char **, t_rt_file_requirements *);
	const int	function_index = get_function_index(scene_content_line[0]);

	if (function_index < 0)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		invalid_scene_content_line(scene_content_line);
		return (-1);
	}
	parse_line[0] = &parse_ambient_light;
	parse_line[1] = &parse_camera;
	parse_line[2] = &parse_light;
	parse_line[3] = &parse_sphere;
	parse_line[4] = &parse_plane;
	parse_line[5] = &parse_cylinder;
	parse_line[6] = &parse_cone;
	parse_line[7] = &parse_material;
	if (parse_line[function_index](engine, scene_content_line,
		rt_file_requirements) < 0)
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
		"co",
		"ma",
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

static bool	are_requirements_met(t_rt_file_requirements rt_file_requirements)
{
	return (rt_file_requirements.ambient_light
		&& rt_file_requirements.camera);
	// TODO add rt_file_requirements.light for mandatory part
}
