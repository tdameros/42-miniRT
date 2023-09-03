/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:19:04 by vfries            #+#    #+#             */
/*   Updated: 2023/04/21 03:29:52 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "engine.h"
#include "parsing.h"


int	parse_ambient_light(t_engine *minirt, char **scene_content_line,
						   t_rt_file_requirements *rt_file_requirements, t_list **object_list)
{
	(void)object_list;
	if (rt_file_requirements->ambient_light == true)
		return (error("Error\nAmbient light already defined\n"));
	if (ft_split_len(scene_content_line) != 3)
		return (error("Error\nFailed to get ambient light line\n"));
	if (get_lighting_ratio(scene_content_line[1],
			&minirt->raytracing_data.ambient_light.lighting_ratio) < 0)
		return (error("Error\nFailed to get ambient light ratio\n"));
	if (get_color(scene_content_line[2],
			&minirt->raytracing_data.ambient_light.color) < 0)
		return (error("Error\nFailed to get ambient light albedo\n"));
	rt_file_requirements->ambient_light = true;
	return (0);
}
