#include <errno.h>

#include "libft.h"

int	get_double(char *double_string, double *double_destination)
{
	const double	double_value = ft_atof(double_string);

	if (errno == ERANGE || errno == EINVAL)
		return (-1);
	*double_destination = double_value;
	return (0);
}
