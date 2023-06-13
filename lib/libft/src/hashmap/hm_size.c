/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_size.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:30:19 by vfries            #+#    #+#             */
/*   Updated: 2023/01/27 05:51:19 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashmap.h"

/// @brief 			Returns the number of elements in hashmap
/// @param hashmap 	Hashmap in which the number of elem is counted
/// @return 		Returns the number of elements in hashmap
int	ft_hm_size(t_hashmap hashmap)
{
	int		size;
	int		i;
	t_list	*cursor;

	if (hashmap == NULL)
		return (0);
	size = 0;
	i = HASHMAP_ARR_SIZE;
	while (i-- > 0)
	{
		cursor = hashmap[i];
		while (cursor != NULL)
		{
			size++;
			cursor = cursor->next;
		}
	}
	return (size);
}
