/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoll.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 12:19:01 by vfries            #+#    #+#             */
/*   Updated: 2023/02/12 20:57:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_char.h"
#include <limits.h>
#include <stdbool.h>
#include <sys/errno.h>

static long long	handle_overflow(bool is_negative, long long tmp_number,
						char next_char);

long long	ft_atoll(const char *str)
{
	long long	result;
	long long	tmp;
	bool		is_negative;

	while (ft_isspace(*str))
		str++;
	is_negative = *str == '-';
	if (*str == '+' || *str == '-')
		str++;
	if (*str < '0' || *str > '9')
		errno = EINVAL;
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		tmp = result * 10 + *str++ - '0';
		if (tmp < result)
			return (handle_overflow(is_negative, tmp, *str));
		result = tmp;
	}
	if (*str != '\0')
		errno = EINVAL;
	if (is_negative)
		return (-result);
	return (result);
}

static long long	handle_overflow(bool is_negative, long long tmp_number,
						char next_char)
{
	if (is_negative)
	{
		if (tmp_number != LLONG_MIN || ft_isdigit(next_char))
			errno = ERANGE;
		return (LLONG_MIN);
	}
	errno = ERANGE;
	return (LLONG_MAX);
}
