/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:19:07 by vfries            #+#    #+#             */
/*   Updated: 2023/04/21 03:27:11 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "struct/t_minirt.h"
#include "struct/t_rt_file_requirements.h"
#include "init.h"

int	parse_cylinder(t_minirt *minirt, char **scene_content_line,
		t_rt_file_requirements *rt_file_requirements, t_list **object_list)
{
	t_object	cylinder;

	(void)minirt;
	(void)rt_file_requirements;
	ft_bzero(&cylinder, sizeof(t_object));
	cylinder.type = CYLINDER;
	if (ft_split_len(scene_content_line) != 6)
		return (error("Error\nFailed to get cylinder line\n"));
	if (get_position(scene_content_line[1], &cylinder.position) < 0)
		return (error("Error\nFailed to get cylinder position\n"));
	if (get_normalized_vector(scene_content_line[2], &cylinder.normal) < 0)
		return (error("Error\nFailed to get cylinder orientation\n"));
	if (get_double(scene_content_line[3], &cylinder.diameter) < 0)
		return (error("Error\nFailed to get cylinder diameter\n"));
	if (get_double(scene_content_line[4], &cylinder.height) < 0)
		return (error("Error\nFailed to get cylinder height\n"));
	if (get_color(scene_content_line[5], &cylinder.color) < 0)
		return (error("Error\nFailed to get cylinder color\n"));
	return (add_object_to_object_list(object_list, cylinder));
}
