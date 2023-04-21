#include "libft.h"

#include "struct/t_minirt.h"
#include "struct/t_rt_file_requirements.h"
#include "init.h"

int	parse_plane(t_minirt *minirt, char **scene_content_line,
		t_rt_file_requirements *rt_file_requirements, t_list **object_list)
{
	t_object plane;

	(void)minirt;
	(void)rt_file_requirements;
	ft_bzero(&plane, sizeof(t_object));
	plane.type = PLANE;
	if (ft_split_len(scene_content_line) != 4)
	{
		ft_putstr_fd("Error\nFailed to get plane line\n", STDERR_FILENO);
		return (-1);
	}
	if (get_position(scene_content_line[1], &plane.position) < 0)
	{
		ft_putstr_fd("Error\nFailed to get plane position\n", STDERR_FILENO);
		return (-1);
	}
	if (get_normalized_vector(scene_content_line[2], &plane.normal) < 0)
	{
		ft_putstr_fd("Error\nFailed to get plane normal\n", STDERR_FILENO);
		return (-1);
	}
	if (get_color(scene_content_line[3], &plane.color) < 0)
	{
		ft_putstr_fd("Error\nFailed to get plane color\n", STDERR_FILENO);
		return (-1);
	}
	return (add_object_to_object_list(object_list, plane));
}
