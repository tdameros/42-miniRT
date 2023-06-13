/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_join_strs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 01:53:00 by vfries            #+#    #+#             */
/*   Updated: 2023/03/05 01:53:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_linked_list.h"
#include "ft_string.h"

char	*ft_lst_join_strs(t_list *str_list)
{
	char	**strs;
	char	*final_str;
	size_t	i;

	strs = malloc(sizeof(*strs) * (ft_lstsize(str_list) + 1));
	if (strs == NULL)
		return (NULL);
	i = 0;
	while (str_list != NULL && str_list->content != NULL)
	{
		strs[i++] = str_list->content;
		str_list = str_list->next;
	}
	strs[i] = NULL;
	final_str = ft_join_strs(strs, "");
	free(strs);
	return (final_str);
}
