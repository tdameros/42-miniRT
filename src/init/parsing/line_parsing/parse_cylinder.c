#include "libft.h"

#include "struct/t_minirt.h"
#include "struct/t_rt_file_requirements.h"
#include "init.h"

int	parse_cylinder(t_minirt *minirt, char **scene_content_line,
		t_rt_file_requirements *rt_file_requirements, t_list **object_list)
{
	t_object cylinder;

	(void)minirt;
	(void)rt_file_requirements;
	ft_bzero(&cylinder, sizeof(t_object));
	cylinder.type = CYLINDER;
	if (ft_split_len(scene_content_line) != 6)
	{
		ft_putstr_fd("Error\nFailed to get cylinder line\n", STDERR_FILENO);
		return (-1);
	}
	if (get_position(scene_content_line[1], &cylinder.position) < 0)
	{
		ft_putstr_fd("Error\nFailed to get cylinder position\n", STDERR_FILENO);
		return (-1);
	}
	if (get_normalized_vector(scene_content_line[2], &cylinder.normal) < 0)
	{
		ft_putstr_fd("Error\nFailed to get cylinder orientation\n", STDERR_FILENO);
		return (-1);
	}
	if (get_double(scene_content_line[3], &cylinder.diameter) < 0)
	{
		ft_putstr_fd("Error\nFailed to get cylinder diameter\n", STDERR_FILENO);
		return (-1);
	}
	if (get_double(scene_content_line[4], &cylinder.height) < 0)
	{
		ft_putstr_fd("Error\nFailed to get cylinder height\n", STDERR_FILENO);
		return (-1);
	}
	if (get_color(scene_content_line[5], &cylinder.color) < 0)
	{
		ft_putstr_fd("Error\nFailed to get cylinder color\n", STDERR_FILENO);
		return (-1);
	}
	return (add_object_to_object_list(object_list, cylinder));
}
