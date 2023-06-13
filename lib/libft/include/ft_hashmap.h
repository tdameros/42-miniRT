/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashmap.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:23:47 by vfries            #+#    #+#             */
/*   Updated: 2023/01/28 06:58:02 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HASHMAP_H
# define FT_HASHMAP_H

# include "ft_linked_list.h"

# define HASHMAP_ARR_SIZE 50

typedef t_list**	t_hashmap;

typedef struct s_hashmap_content
{
	char	*target;
	void	*content;
}	t_hashmap_content;

int					ft_hm_add_elem(t_hashmap dst, char *target, void *content,
						void (*del)(void *));
int					ft_hm_delete_elem(t_hashmap map,
						char *target, void (*del)(void *));
void				ft_hm_clear(t_hashmap *map, void (*del)(void *));
void				*ft_hm_get_content(t_hashmap map, char *target);
t_hashmap_content	*ft_hm_get_elem(t_hashmap map, char *target);
size_t				ft_hm_get_index(char *target);
t_hashmap			ft_hm_init(void);
int					ft_hm_size(t_hashmap hashmap);

#endif
