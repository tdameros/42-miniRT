/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmask_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:41:59 by vfries            #+#    #+#             */
/*   Updated: 2023/02/26 16:50:48 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bitmask.h"
#include "ft_mem.h"

int	ft_bitmask_init(t_bitmask *bitmask, size_t size)
{
	if (size % 8 == 0)
		bitmask->arr = ft_calloc(size / 8, sizeof(*bitmask->arr));
	else
		bitmask->arr = ft_calloc(size / 8 + 1, sizeof(*bitmask->arr));
	return (-(bitmask->arr == NULL));
}
