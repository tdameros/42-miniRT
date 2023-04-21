#include <errno.h>
#include "libft.h"

#include "struct/t_minirt.h"
#include "struct/t_rt_file_requirements.h"
#include "init.h"

static int	get_camera_fov(char *fov_string, double *fov_destination);

int	parse_camera(t_minirt *minirt, char **scene_content_line,
		t_rt_file_requirements *rt_file_requirements, t_list **object_list)
{
	(void)object_list;
	if (rt_file_requirements->camera == true)
	{
		ft_putstr_fd("Error\nCamera already defined\n", STDERR_FILENO);
		return (-1);
	}
	if (ft_split_len(scene_content_line) != 4)
	{
		ft_putstr_fd("Error\nFailed to get camera line\n", STDERR_FILENO);
		return (-1);
	}
	if (get_position(scene_content_line[1],
			&minirt->raytracing_data.camera.position) < 0)
	{
		ft_putstr_fd("Error\nFailed to get camera position\n", STDERR_FILENO);
		return (-1);
	}
	if (get_normalized_vector(scene_content_line[2],
			&minirt->raytracing_data.camera.orientation) < 0)
	{
		ft_putstr_fd("Error\nFailed to get camera orientation\n",
			STDERR_FILENO);
		return (-1);
	}
	if (get_camera_fov(scene_content_line[3],
			&minirt->raytracing_data.camera.fov) < 0)
	{
		ft_putstr_fd("Error\nFailed to get camera fov\n", STDERR_FILENO);
		return (-1);
	}
	rt_file_requirements->camera = true;
	return (0);
}

static int	get_camera_fov(char *fov_string, double *fov_destination)
{
	const double	fov = ft_atof(fov_string);

	if (errno == EINVAL || errno == ERANGE || fov < 0 || fov > 180)
		return (-1);
	*fov_destination = fov;
	return (0);
}
