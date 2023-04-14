/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmask_get_position.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:08:13 by vfries            #+#    #+#             */
/*   Updated: 2023/02/26 16:33:30 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bitmask.h"

void	ft_bitmask_get_position(size_t target, size_t *index,
			int8_t *right_shift)
{
	*index = target / 8;
	*right_shift = 7 - target % 8;
}
