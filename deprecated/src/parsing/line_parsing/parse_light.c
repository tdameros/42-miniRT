/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:19:09 by vfries            #+#    #+#             */
/*   Updated: 2023/04/21 03:26:45 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "engine.h"
#include "parsing.h"

int	parse_light(t_engine *minirt, char **scene_content_line,
				   t_rt_file_requirements *rt_file_requirements, t_list **object_list)
{
	(void)object_list;
	if (rt_file_requirements->light == true)
		return (error("Error\nLight already defined\n"));
	if (ft_split_len(scene_content_line) != 4)
		return (error("Error\nFailed to get light line\n"));
	if (get_position(scene_content_line[1],
			&minirt->raytracing_data.light.position) < 0)
		return (error("Error\nFailed to get light position\n"));
	if (get_lighting_ratio(scene_content_line[2],
			&minirt->raytracing_data.light.brightness) < 0)
		return (error("Error\nFailed to get light ratio\n"));
	if (get_color(scene_content_line[3],
			&minirt->raytracing_data.light.color) < 0)
		return (error("Error\nFailed to get light albedo\n"));
	rt_file_requirements->light = true;
	return (0);
}
