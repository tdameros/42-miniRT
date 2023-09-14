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

#include "engine.h"
#include "parsing.h"
#include "ray_tracer_gui_api.h"

int	parse_cylinder(t_engine *engine, char **scene_content_line,
		t_rt_file_requirements *rt_file_requirements)
{
	t_object	cylinder;

	(void)rt_file_requirements;
	ft_bzero(&cylinder, sizeof(cylinder));
	if (ft_split_len(scene_content_line) != 6)
		return (error("Error\nFailed to get cylinder line\n"));
	if (get_position(scene_content_line[1], &cylinder.position) < 0)
		return (error("Error\nFailed to get cylinder position\n"));
	if (get_normalized_vector(scene_content_line[2], &cylinder.axis) < 0)
		return (error("Error\nFailed to get cylinder orientation\n"));
	if (get_float(scene_content_line[3], &cylinder.radius) < 0)
		return (error("Error\nFailed to get cylinder radius\n"));
	cylinder.radius /= 2.f;
	if (get_float(scene_content_line[4], &cylinder.height) < 0)
		return (error("Error\nFailed to get cylinder y\n"));
	if (get_color(scene_content_line[5], &cylinder.material.albedo) < 0)
		return (error("Error\nFailed to get cylinder albedo\n"));
	cylinder.material.albedo = vector3f_divide(cylinder.material.albedo, 255.f);
	cylinder = cylinder_create(cylinder.position, cylinder.axis, \
		(t_object_size){cylinder.radius, cylinder.height}, cylinder.material);
	if (add_object(engine, cylinder) < 0)
		return (free_object(&cylinder), -1);
	return (0);
}
