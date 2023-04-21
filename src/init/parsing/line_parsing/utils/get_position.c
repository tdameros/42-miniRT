#include <errno.h>
#include "struct/t_minirt.h"
#include "libft.h"

int	get_position(char *position_string, t_vector_3d *position_destination)
{
	char	**position_split;

	position_split = ft_split(position_string, ',');
	if (position_split == NULL)
		return (-1);
	if (ft_split_len(position_split) != 3)
	{
		ft_free_split(position_split);
		return (-1);
	}
	position_destination->x = ft_atof(position_split[0]);
	position_destination->y = ft_atof(position_split[1]);
	position_destination->z = ft_atof(position_split[2]);
	ft_free_split(position_split);
	if (errno == ERANGE || errno == EINVAL)
		return (-1);
	return (0);
}
