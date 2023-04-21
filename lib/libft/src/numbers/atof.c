#include <errno.h>
#include <math.h>

#include "libft.h"

static int	get_pre_decimal(const char **string, double *result);
static int	get_post_decimal(const char **string, double *result);

double	ft_atof(const char *string)
{
	double	result;
	int		new_errno_value;
	bool	is_negative;

	is_negative = *string == '-';
	string += is_negative || *string == '+';
	if (*string == '\0')
	{
		errno = EINVAL;
		return (0);
	}
	new_errno_value = get_pre_decimal(&string, &result);
	if (new_errno_value != 0)
	{
		errno = new_errno_value;
		return (0);
	}
	new_errno_value = get_post_decimal(&string, &result);
	if (new_errno_value != 0)
	{
		errno = new_errno_value;
		return (0);
	}
	return (result * (-is_negative + !is_negative));
}

static int	get_pre_decimal(const char **string, double *result)
{
	*result = 0;
	while (ft_isdigit(**string))
	{
		*result = *result * 10 + **string - '0';
		(*string)++;
	}
	if (**string != '.' && **string != '\0')
		return (EINVAL);
	return (ERANGE * (isinf(*result) != 0));
}

static int	get_post_decimal(const char **string, double *result)
{
	size_t	post_decimal;

	if (**string == '\0')
		return (0);
	(*string)++;
	post_decimal = 10;
	while (ft_isdigit(**string))
	{
		(*result) += (double)(**string - '0') / (double)post_decimal;
		post_decimal *= 10;
		(*string)++;
	}
	if (**string != '\0')
		return (EINVAL);
	return (ERANGE * (isinf(*result) != 0));
}
