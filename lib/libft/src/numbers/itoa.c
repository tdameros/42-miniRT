/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:18:37 by vfries            #+#    #+#             */
/*   Updated: 2023/01/09 01:03:31 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_itoa(int n)
{
	char	buf[12];
	char	*buf_ptr;
	char	is_negative;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n = -n;
		is_negative = 1;
	}
	else
		is_negative = 0;
	buf[11] = '\0';
	buf_ptr = buf + 10;
	while (n > 0)
	{
		*buf_ptr-- = n % 10 + '0';
		n /= 10;
	}
	if (is_negative)
		*buf_ptr-- = '-';
	return (ft_strdup(buf_ptr + 1));
}
