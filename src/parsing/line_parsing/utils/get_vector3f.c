#include <errno.h>

#include "libft.h"

#include "math/vector.h"

int	get_vector3f(const char *vector3f_string, t_vector3f *vector3f_destination)
{
	char	**vector3f_split;

	vector3f_split = ft_split(vector3f_string, ',');
	if (vector3f_split == NULL)
		return (-1);
	if (ft_split_len(vector3f_split) != 3)
	{
		ft_free_split(vector3f_split);
		return (-1);
	}
	vector3f_destination->x = ft_atof(vector3f_split[0]);
	vector3f_destination->y = ft_atof(vector3f_split[1]);
	vector3f_destination->z = ft_atof(vector3f_split[2]);
	ft_free_split(vector3f_split);
	if (errno == ERANGE || errno == EINVAL)
		return (-1);
	return (0);
}
