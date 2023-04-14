/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmask_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:04:06 by vfries            #+#    #+#             */
/*   Updated: 2023/02/25 13:05:01 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_bitmask.h"

void	ft_bitmask_free(t_bitmask *bitmask)
{
	free(bitmask->arr);
	bitmask->arr = NULL;
}
