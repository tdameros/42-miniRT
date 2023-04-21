#include <errno.h>

#include "libft.h"

int	get_lighting_ratio(char *lighting_ratio_string,
		double *lighting_ratio_destination)
{
	const double	lighting_ratio = ft_atof(lighting_ratio_string);

	if (lighting_ratio < 0.0 || lighting_ratio > 1.0
		|| errno == ERANGE || errno == EINVAL)
		return (-1);
	*lighting_ratio_destination = lighting_ratio;
	return (0);
}
