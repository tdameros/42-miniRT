/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmask_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:34:28 by vfries            #+#    #+#             */
/*   Updated: 2023/03/01 12:35:03 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bitmask.h"

void	ft_bitmask_set(t_bitmask bitmask, size_t target, bool new_value)
{
	size_t		index;
	int8_t		right_shift;
	uint8_t		tmp;
	uint8_t		i;
	uint8_t		power;

	ft_bitmask_get_position(target, &index, &right_shift);
	tmp = 0;
	i = 0;
	power = 1;
	while (i < 8)
	{
		if (i != right_shift)
			tmp |= (bitmask.arr[index] >> i) % 2 * power;
		power *= 2;
		i++;
	}
	tmp |= new_value << right_shift;
	bitmask.arr[index] = tmp;
}
