/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sum_uint8_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:32:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/20 15:32:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <errno.h>
#include <stdint.h>

uint64_t	ft_sum_uint8_arr(const uint8_t *arr, size_t size)
{
	uint64_t	tmp;
	uint64_t	result;

	errno = 0;
	result = 0;
	while (size--)
	{
		tmp = result + arr[size];
		if (tmp < result)
			errno = ERANGE;
		result = tmp;
	}
	return (result);
}
