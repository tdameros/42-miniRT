/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:23:46 by vfries            #+#    #+#             */
/*   Updated: 2023/01/09 01:03:29 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	long	result;
	char	is_negative;

	while (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		str++;
	is_negative = *str == '-';
	if (*str == '+' || *str == '-')
		str++;
	result = 0;
	while (*str >= '0' && *str <= '9')
		result = result * 10 + *str++ - '0';
	if (is_negative)
		return (-result);
	return (result);
}
