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
	double	nb_to_add;

	*result = 0;
	while (ft_isdigit(**string))
	{
		if (*result > *result * 10)
			return (ERANGE);
		(*result) *= 10;
		nb_to_add = **string - '0';
		if (nb_to_add > HUGE_VAL - *result)
			return (ERANGE);
		(*result) += nb_to_add;
		(*string)++;
	}
	if (**string != '.' && **string != '\0')
		return (EINVAL);
	return (0);
}

static int	get_post_decimal(const char **string, double *result)
{
	size_t	post_decimal;
	double	nb_to_add;

	if (**string == '\0')
		return (0);
	(*string)++;
	post_decimal = 10;
	while (ft_isdigit(**string))
	{
		nb_to_add = (double)(**string - '0') / (double)post_decimal;
		if (nb_to_add > HUGE_VAL - *result)
			return (ERANGE);
		*result = *result + nb_to_add;
		(*string)++;
		post_decimal *= 10;
	}
	if (**string != '\0')
		return (EINVAL);
	return (0);
}
