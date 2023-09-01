#include <stdbool.h>
#include <stddef.h>

#include "ft_string.h"

bool	ft_strs_are_equal(char **strs1, char **strs2)
{
	size_t	i;

	if (strs1 == strs2)
		return (true);
	if (strs1 == NULL || strs2 == NULL)
		return (false);
	i = -1;
	while (strs1[++i] != NULL)
	{
		if (strs2[i] == NULL)
			return (false);
		if (ft_strcmp(strs1[i], strs2[i]) != 0)
			return (false);
	}
	return (strs2[i] == NULL);
}
