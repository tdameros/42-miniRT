/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_get_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:24:00 by vfries            #+#    #+#             */
/*   Updated: 2023/01/17 16:39:16 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashmap.h"
#include "ft_string.h"

/// @brief 			returns the t_hashmap_content* (a) in the hashmap that has
///						a->target == target, returns NULL if it doesn't exist
/// @param map 		Hashmap in which to search for target
/// @param target 	string to look for in the hashmap
/// @return 		returns the t_hashmap_content* (a) in the hashmap that has
///						a->target == target, returns NULL if it doesn't exist
t_hashmap_content	*ft_hm_get_elem(t_hashmap map, char *target)
{
	t_list	*cursor;

	if (target == NULL)
		return (NULL);
	cursor = map[ft_hm_get_index(target)];
	while (cursor != NULL
		&& ft_strcmp(((t_hashmap_content *)cursor->content)->target, target)
		!= 0)
		cursor = cursor->next;
	if (cursor == NULL)
		return (NULL);
	return (cursor->content);
}
