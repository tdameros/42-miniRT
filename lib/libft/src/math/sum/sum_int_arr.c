/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sum_int_arr.c                                      :+:      :+:    :+:   */
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

int64_t	ft_sum_int_arr(const int *arr, size_t size)
{
	int64_t	tmp;
	int64_t	result;

	errno = 0;
	result = 0;
	while (size--)
	{
		tmp = result + arr[size];
		if ((arr[size] < 0 && tmp > result) || (arr[size] > 0 && tmp < result))
			errno = ERANGE;
		result = tmp;
	}
	return (result);
}
