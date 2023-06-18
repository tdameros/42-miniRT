/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:19:10 by vfries            #+#    #+#             */
/*   Updated: 2023/04/21 03:26:15 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "engine.h"
#include "parsing.h"

int	parse_plane(t_engine *minirt, char **scene_content_line,
				   t_rt_file_requirements *rt_file_requirements, t_list **object_list)
{
	t_object	plane;

	(void)minirt;
	(void)rt_file_requirements;
	ft_bzero(&plane, sizeof(t_object));
	plane.type = PLANE;
	if (ft_split_len(scene_content_line) != 4)
		return (error("Error\nFailed to get plane line\n"));
	if (get_position(scene_content_line[1], &plane.position) < 0)
		return (error("Error\nFailed to get plane position\n"));
	if (get_normalized_vector(scene_content_line[2], &plane.normal) < 0)
		return (error("Error\nFailed to get plane normal\n"));
	if (get_color(scene_content_line[3], &plane.material.albedo) < 0)
		return (error("Error\nFailed to get plane albedo\n"));
	return (add_object_to_object_list(object_list, plane));
}
