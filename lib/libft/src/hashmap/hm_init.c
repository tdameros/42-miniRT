/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:30:27 by vfries            #+#    #+#             */
/*   Updated: 2023/01/17 16:40:39 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashmap.h"
#include "ft_mem.h"

/// @brief 		Mallocs a hashmap and sets all its t_list to NULL
/// @return 	Returns an empty hashmap
t_hashmap	ft_hm_init(void)
{
	return (ft_calloc(HASHMAP_ARR_SIZE, sizeof(t_hashmap)));
}
