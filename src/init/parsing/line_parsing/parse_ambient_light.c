#include "libft.h"

#include "struct/t_minirt.h"
#include "struct/t_rt_file_requirements.h"
#include "init.h"

int	parse_ambient_light(t_minirt *minirt, char **scene_content_line,
		t_rt_file_requirements *rt_file_requirements, t_list **object_list)
{
	(void)object_list;
	if (rt_file_requirements->ambient_light == true)
	{
		ft_putstr_fd("Error\nAmbient light already defined\n", STDERR_FILENO);
		return (-1);
	}
	if (ft_split_len(scene_content_line) != 3)
	{
		ft_putstr_fd("Error\nFailed to get ambient light line\n",
			STDERR_FILENO);
		return (-1);
	}
	if (get_lighting_ratio(scene_content_line[1],
			&minirt->raytracing_data.ambient_light.lighting_ratio) < 0)
	{
		ft_putstr_fd("Error\nFailed to get ambient light ratio\n",
			STDERR_FILENO);
		return (-1);
	}
	if (get_color(scene_content_line[2],
			&minirt->raytracing_data.ambient_light.color) < 0)
	{
		ft_putstr_fd("Error\nFailed to get ambient light color\n",
			STDERR_FILENO);
		return (-1);
	}
	rt_file_requirements->ambient_light = true;
	return (0);
}
