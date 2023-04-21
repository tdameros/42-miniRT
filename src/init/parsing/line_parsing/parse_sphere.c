#include "libft.h"

#include "struct/t_minirt.h"
#include "struct/t_rt_file_requirements.h"
#include "init.h"

int	parse_sphere(t_minirt *minirt, char **scene_content_line,
		t_rt_file_requirements *rt_file_requirements, t_list **object_list)
{
	t_object	sphere;

	(void)minirt;
	(void)rt_file_requirements;
	ft_bzero(&sphere, sizeof(t_object));
	sphere.type = SPHERE;
	if (ft_split_len(scene_content_line) != 4)
	{
		ft_putstr_fd("Error\nFailed to get sphere line\n", STDERR_FILENO);
		return (-1);
	}
	if (get_position(scene_content_line[1], &sphere.position) < 0)
	{
		ft_putstr_fd("Error\nFailed to get sphere position\n", STDERR_FILENO);
		return (-1);
	}
	if (get_double(scene_content_line[2], &sphere.diameter) < 0)
	{
		ft_putstr_fd("Error\nFailed to get sphere radius\n", STDERR_FILENO);
		return (-1);
	}
	if (get_color(scene_content_line[3], &sphere.color) < 0)
	{
		ft_putstr_fd("Error\nFailed to get sphere color\n", STDERR_FILENO);
		return (-1);
	}
	return (add_object_to_object_list(object_list, sphere));
}
