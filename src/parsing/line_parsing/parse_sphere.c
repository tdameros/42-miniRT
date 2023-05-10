/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:19:12 by vfries            #+#    #+#             */
/*   Updated: 2023/04/21 03:25:35 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "engine.h"
#include "struct/t_rt_file_requirements.h"
#include "init.h"

int	parse_sphere(t_engine *minirt, char **scene_content_line,
					t_rt_file_requirements *rt_file_requirements, t_list **object_list)
{
	t_object	sphere;

	(void)minirt;
	(void)rt_file_requirements;
	ft_bzero(&sphere, sizeof(t_object));
	sphere.type = SPHERE;
	if (ft_split_len(scene_content_line) != 4)
		return (error("Error\nFailed to get sphere line\n"));
	if (get_position(scene_content_line[1], &sphere.position) < 0)
		return (error("Error\nFailed to get sphere position\n"));
	if (get_double(scene_content_line[2], &sphere.radius) < 0)
		return (error("Error\nFailed to get sphere radius\n"));
	if (get_color(scene_content_line[3], &sphere.albedo) < 0)
		return (error("Error\nFailed to get sphere albedo\n"));
	return (add_object_to_object_list(object_list, sphere));
}
