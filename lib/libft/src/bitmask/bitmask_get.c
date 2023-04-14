/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmask_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:30:17 by vfries            #+#    #+#             */
/*   Updated: 2023/02/25 13:37:18 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bitmask.h"

bool	ft_bitmask_get(t_bitmask bitmask, size_t target)
{
	size_t	index;
	int8_t	right_shift;

	ft_bitmask_get_position(target, &index, &right_shift);
	return ((bitmask.arr[index] >> right_shift) % 2);
}
