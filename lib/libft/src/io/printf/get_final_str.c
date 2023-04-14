/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_final_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:42:11 by vfries            #+#    #+#             */
/*   Updated: 2022/11/20 04:09:52 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linked_list.h"
#include "ft_string.h"
#include <stdlib.h>

void	free_content(void *content)
{
	if (content != (void *)-1)
		free(content);
}

int	get_final_str_len(t_list *str_list)
{
	int		len;

	len = 0;
	while (str_list)
	{
		if (str_list->content == (void *)-1)
			len++;
		else
			len += ft_strlen(str_list->content);
		str_list = str_list->next;
	}
	return (len);
}

void	copy_str_and_increment_final_str(char **final_str, const char *node_str)
{
	while (*node_str)
		*(*final_str)++ = *node_str++;
}

void	fill_final_str(char *final_str, t_list *str_list)
{
	t_list	*current;

	current = str_list;
	while (current)
	{
		if (current->content == (void *)-1)
			*final_str++ = '\0';
		else
			copy_str_and_increment_final_str(&final_str, current->content);
		current = current->next;
	}
}

char	*get_final_str(t_list *str_list, int *char_written)
{
	char	*final_str;

	*char_written = get_final_str_len(str_list);
	final_str = malloc(*char_written + 1);
	if (final_str == NULL)
		return (NULL);
	fill_final_str(final_str, str_list);
	return (final_str);
}
