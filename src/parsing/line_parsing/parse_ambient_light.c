/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:19:04 by vfries            #+#    #+#             */
/*   Updated: 2023/09/03 11:06:56 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "engine.h"
#include "parsing.h"

int	parse_ambient_light(t_engine *engine, char **scene_content_line,
		t_rt_file_requirements *rt_file_requirements)
{
	t_light	light;

	ft_bzero(&light, sizeof(light));
	if (rt_file_requirements->ambient_light == true)
		return (error("Error\nAmbient light already defined\n"));
	if (ft_split_len(scene_content_line) != 3)
		return (error("Error\nFailed to get ambient light line\n"));
	if (get_lighting_ratio(scene_content_line[1], &light.brightness) < 0)
		return (error("Error\nFailed to get ambient light ratio\n"));
	if (get_color(scene_content_line[2], &light.color) < 0)
		return (error("Error\nFailed to get ambient light albedo\n"));
	light.color = vector3f_divide(light.color, 255.f);
	light = light_create((t_vector3f){0}, light.color, light.brightness);
	free(light.name);
	light.name = ft_strdup("Ambient light");
	engine->scene.ambient_light = light;
	rt_file_requirements->ambient_light = true;
	return (0);
}
