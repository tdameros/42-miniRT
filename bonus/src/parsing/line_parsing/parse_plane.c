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
#include "ray_tracer_gui_api.h"

int	parse_plane(t_engine *engine, char **scene_content_line,
		t_rt_file_requirements *rt_file_requirements)
{
	t_object	plane;

	(void)rt_file_requirements;
	ft_bzero(&plane, sizeof(plane));
	if (ft_split_len(scene_content_line) != 4)
		return (error("Error\nFailed to get plane line\n"));
	if (get_position(scene_content_line[1], &plane.position) < 0)
		return (error("Error\nFailed to get plane position\n"));
	if (get_rotation(scene_content_line[2], &plane.axis_degrees) < 0)
		return (error("Error\nFailed to get plane axis\n"));
	if (get_color(scene_content_line[3], &plane.material.albedo) < 0)
		return (error("Error\nFailed to get plane albedo\n"));
	plane.material.albedo = vector3f_divide(plane.material.albedo, 255.f);
	plane = plane_create(plane.position, plane.axis_degrees, plane.material);
	if (add_object(engine, plane) < 0)
		return (free_object(&plane), -1);
	return (0);
}
