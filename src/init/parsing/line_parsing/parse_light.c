#include "libft.h"

#include "struct/t_minirt.h"
#include "struct/t_rt_file_requirements.h"
#include "init.h"

int	parse_light(t_minirt *minirt, char **scene_content_line,
		t_rt_file_requirements *rt_file_requirements, t_list **object_list)
{
	(void)object_list;
	if (rt_file_requirements->light == true)
	{
		ft_putstr_fd("Error\nLight already defined\n", STDERR_FILENO);
		return (-1);
	}
	if (ft_split_len(scene_content_line) != 4)
	{
		ft_putstr_fd("Error\nFailed to get light line\n", STDERR_FILENO);
		return (-1);
	}
	if (get_position(scene_content_line[1],
			&minirt->raytracing_data.light.position) < 0)
	{
		ft_putstr_fd("Error\nFailed to get light position\n", STDERR_FILENO);
		return (-1);
	}
	if (get_lighting_ratio(scene_content_line[2],
			&minirt->raytracing_data.light.brightness) < 0)
	{
		ft_putstr_fd("Error\nFailed to get light ratio\n", STDERR_FILENO);
		return (-1);
	}
	if (get_color(scene_content_line[3],
			&minirt->raytracing_data.light.color) < 0)
	{
		ft_putstr_fd("Error\nFailed to get light color\n", STDERR_FILENO);
		return (-1);
	}
	rt_file_requirements->light = true;
	return (0);
}
