/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_get_index.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:36:28 by vfries            #+#    #+#             */
/*   Updated: 2023/01/17 16:37:26 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashmap.h"

/// @brief 			Returns the index of the t_list where target could be found
///						if it is in the hashmap
/// @param target 	String from which the index is generated
/// @return 		Returns the index of the t_list where target could be found
///						if it is in the hashmap
size_t	ft_hm_get_index(char *target)
{
	size_t	target_value;
	size_t	multiplier;
	size_t	i;

	target_value = 0;
	multiplier = 1;
	i = 0;
	while (target[i] != '\0')
	{
		target_value += target[i] * multiplier;
		multiplier *= 10;
		i++;
	}
	return (target_value % HASHMAP_ARR_SIZE);
}
