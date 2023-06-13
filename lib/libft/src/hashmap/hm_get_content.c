/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_get_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:30:32 by vfries            #+#    #+#             */
/*   Updated: 2023/01/17 16:38:36 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashmap.h"

/// @brief 			Returns hashmap content at target,
///						returns NULL if it doesn't exist
/// @param map 		Hashmap in which to search for target
/// @param target 	Where the content is stored in hashmap
/// @return 		Returns hashmap content at target,
///						returns NULL if it doesn't exist
void	*ft_hm_get_content(t_hashmap map, char *target)
{
	t_hashmap_content	*elem;

	elem = ft_hm_get_elem(map, target);
	if (elem == NULL)
		return (NULL);
	return (elem->content);
}
