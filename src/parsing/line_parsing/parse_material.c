/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 11:06:10 by vfries            #+#    #+#             */
/*   Updated: 2023/09/03 11:06:11 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	change_material(t_engine *engine, char *instructions);
static int	get_function_to_call_index(char **instructions_split);
static void	call_function(t_engine *engine, char *arg, int function_index);

int	parse_material(t_engine *engine, char **scene_content_line,
		t_rt_file_requirements *rt_file_requirements)
{
	size_t	i;

	(void)rt_file_requirements;
	if (engine->scene.objects.length == 0)
	{
		ft_print_error("Warning: Failed to change material during parsing as "
			"no objects were created\n");
		return (0);
	}
	i = 0;
	while (scene_content_line[++i] != NULL)
		change_material(engine, scene_content_line[i]);
	return (0);
}

static void	change_material(t_engine *engine, char *instructions)
{
	char	**instructions_split;
	int		function_to_call_index;

	instructions_split = ft_split(instructions, ':');
	function_to_call_index = get_function_to_call_index(instructions_split);
	if (instructions_split == NULL || ft_split_len(instructions_split) != 2
		|| function_to_call_index < 0)
	{
		ft_print_error("Warning: Failed to change material during parsing ");
		ft_print_error(instructions);
		ft_print_error("\n");
		return (ft_free_split(instructions_split));
	}
	call_function(engine, instructions_split[1], function_to_call_index);
	ft_free_split(instructions_split);
}

static int	get_function_to_call_index(char **instructions_split)
{
	int			i;
	const char	*functions[] = {
		"reflection",
		"specular",
		"outline_texture",
		"outline_checkerboard",
		"outline_normal_map",
		"cap_texture",
		"cap_checkerboard",
		"cap_normal_map",
	};

	if (instructions_split == NULL || instructions_split[0] == NULL)
		return (-1);
	i = -1;
	while (++i < (int)(sizeof(functions) / sizeof(*functions)))
	{
		if (ft_strcmp(instructions_split[0], functions[i]) == 0)
			return (i);
	}
	return (-1);
}

static void	call_function(t_engine *engine, char *arg, int function_index)
{
	void			(*functions[8])(t_object *, char *arg);

	functions[0] = &parse_reflection;
	functions[1] = &parse_specular;
	functions[2] = &parse_outline_texture;
	functions[3] = &parse_outline_checkerboard;
	functions[4] = &parse_outline_normal_map;
	functions[5] = &parse_cap_texture;
	functions[6] = &parse_cap_checkerboard;
	functions[7] = &parse_cap_normal_map;
	functions[function_index](engine->scene.objects.data
		+ engine->scene.objects.length - 1, arg);
}
