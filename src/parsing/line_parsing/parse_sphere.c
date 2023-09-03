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
#include "parsing.h"
#include "ray_tracer_gui_api.h"

int	parse_sphere(t_engine *engine, char **scene_content_line,
		t_rt_file_requirements *rt_file_requirements)
{
	t_object	sphere;

	(void)rt_file_requirements;
	ft_bzero(&sphere, sizeof(sphere));
	if (ft_split_len(scene_content_line) != 4)
		return (error("Error\nFailed to get sphere line\n"));
	if (get_position(scene_content_line[1], &sphere.position) < 0)
		return (error("Error\nFailed to get sphere position\n"));
	if (get_float(scene_content_line[2], &sphere.radius) < 0)
		return (error("Error\nFailed to get sphere radius\n"));
	sphere.radius /= 2.f;
	if (get_color(scene_content_line[3], &sphere.material.albedo) < 0)
		return (error("Error\nFailed to get sphere albedo\n"));
	sphere.material.albedo = vector3f_divide(sphere.material.albedo, 255.f);
	sphere = sphere_create(sphere.position, sphere.radius, sphere.material);
	return (add_object(engine, sphere));
}
