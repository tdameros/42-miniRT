/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 11:06:04 by vfries            #+#    #+#             */
/*   Updated: 2023/09/03 11:06:07 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ray_tracer_gui_api.h"

int	parse_cone(t_engine *engine, char **scene_content_line,
		t_rt_file_requirements *rt_file_requirements)
{
	t_object	cone;

	(void)rt_file_requirements;
	ft_bzero(&cone, sizeof(cone));
	if (ft_split_len(scene_content_line) != 6)
		return (error("Error\nFailed to get cone line\n"));
	if (get_position(scene_content_line[1], &cone.position) < 0)
		return (error("Error\nFailed to get cone position\n"));
	if (get_normalized_vector(scene_content_line[2], &cone.axis) < 0)
		return (error("Error\nFailed to get cone orientation\n"));
	if (get_float(scene_content_line[3], &cone.radius) < 0)
		return (error("Error\nFailed to get cone radius\n"));
	cone.radius /= 2.f;
	if (get_float(scene_content_line[4], &cone.height) < 0)
		return (error("Error\nFailed to get cone y\n"));
	if (get_color(scene_content_line[5], &cone.material.albedo) < 0)
		return (error("Error\nFailed to get cone albedo\n"));
	cone.material.albedo = vector3f_divide(cone.material.albedo, 255.f);
	cone = cone_create(cone.position, cone.axis, \
		(t_object_size){cone.radius, cone.height}, cone.material);
	if (add_object(engine, cone) < 0)
		return (free_object(&cone), -1);
	return (0);
}
