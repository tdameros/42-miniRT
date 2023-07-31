/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sum_uint8_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:12:26 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/31 09:12:28 by tdameros         ###   ########lyon.fr   */
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
