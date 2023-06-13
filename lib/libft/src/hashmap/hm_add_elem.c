/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_add_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:41:46 by vfries            #+#    #+#             */
/*   Updated: 2023/01/17 16:23:55 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashmap.h"
#include "ft_string.h"
#include <stdlib.h>

#define NOT_FOUND 1
#define MALLOC_FAILED -1
#define SUCCESSFULLY_ADDED 0

static int	modify_if_exists(t_list *dst, char *target, void *content,
				void (*del)(void *));
static int	add_new(t_list **dst, char *target, void *content);

/// @brief 			Used to add an elem to the hashmap
/// @param map 		Hashmap in which to insert the elem
/// @param target 	Used to find the elem in the hashmap
///						(doesn't need to be malloced)
/// @param content 	Content to add to the hashmap
///						(needs to be malloced)
/// @param del 		Fonction to delete content that might already be at target
///						(pass NULL if you don't want to free previous content)
/// @return			0 if successful, -1 if malloc failed
int	ft_hm_add_elem(t_hashmap map, char *target, void *content,
			void (*del)(void *))
{
	size_t	index;

	index = ft_hm_get_index(target);
	if (modify_if_exists(map[index], target, content, del)
		== SUCCESSFULLY_ADDED)
		return (SUCCESSFULLY_ADDED);
	return (add_new(map + index, target, content));
}

static int	modify_if_exists(t_list *dst, char *target, void *content,
				void (*del)(void *))
{
	while (dst != NULL
		&& ft_strcmp(((t_hashmap_content *)dst->content)->target, target) != 0)
		dst = dst->next;
	if (dst == NULL)
		return (NOT_FOUND);
	if (del == NULL)
	{
		((t_hashmap_content *)dst->content)->content = content;
		return (SUCCESSFULLY_ADDED);
	}
	del(((t_hashmap_content *)dst->content)->content);
	((t_hashmap_content *)dst->content)->content = content;
	return (SUCCESSFULLY_ADDED);
}

static int	add_new(t_list **dst, char *target, void *content)
{
	t_hashmap_content	*new_node_content;
	t_list				*new_node;

	new_node_content = malloc(sizeof(t_hashmap_content));
	if (new_node_content == NULL)
		return (MALLOC_FAILED);
	new_node_content->content = content;
	new_node_content->target = ft_strdup(target);
	if (new_node_content->target == NULL)
	{
		free(new_node_content);
		return (MALLOC_FAILED);
	}
	new_node = ft_lstnew(new_node_content);
	if (new_node == NULL)
	{
		free(new_node_content->target);
		free(new_node_content);
		return (MALLOC_FAILED);
	}
	ft_lstadd_front(dst, new_node);
	return (SUCCESSFULLY_ADDED);
}
