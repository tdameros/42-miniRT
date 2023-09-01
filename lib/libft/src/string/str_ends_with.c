#include "ft_string.h"

bool	ft_str_ends_with(const char *str, const char *end)
{
	const size_t	str_len = ft_strlen(str);
	const size_t	end_len = ft_strlen(end);

	if (str_len < end_len)
		return (false);
	return (ft_strcmp(str + str_len - end_len, end) == 0);
}
