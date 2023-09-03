/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:19:05 by vfries            #+#    #+#             */
/*   Updated: 2023/04/21 03:28:52 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "libft.h"

#include "engine.h"
#include "parsing.h"

static int	get_camera_fov(char *fov_string, float *fov_destination);

int	parse_camera(t_engine *minirt, char **scene_content_line,
					t_rt_file_requirements *rt_file_requirements, t_list **object_list)
{
	(void)object_list;
	if (rt_file_requirements->camera == true)
		return (error("Error\nCamera already defined\n"));
	if (ft_split_len(scene_content_line) != 4)
		return (error("Error\nFailed to get camera line\n"));
	if (get_position(scene_content_line[1],
			&minirt->raytracing_data.camera.position) < 0)
		return (error("Error\nFailed to get camera position\n"));
	if (get_normalized_vector(scene_content_line[2],
			&minirt->raytracing_data.camera.direction) < 0)
		return (error("Error\nFailed to get camera orientation\n"));
	if (get_camera_fov(scene_content_line[3],
			&minirt->raytracing_data.camera.horizontal_fov) < 0)
		return (error("Error\nFailed to get camera fov\n"));
	rt_file_requirements->camera = true;
	return (0);
}

static int	get_camera_fov(char *fov_string, float *fov_destination)
{
	const float	fov = ft_atof(fov_string);

	if (errno == EINVAL || errno == ERANGE || fov < 0 || fov > 180)
		return (-1);
	*fov_destination = fov;
	return (0);
}
