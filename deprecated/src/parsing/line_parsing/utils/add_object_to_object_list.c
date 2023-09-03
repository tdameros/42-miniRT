/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_object_to_object_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:19:15 by vfries            #+#    #+#             */
/*   Updated: 2023/04/21 03:19:15 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "object.h"

int	add_object_to_object_list(t_list **object_list, t_object object)
{
	t_list		*new_object;
	t_object	*new_object_content;

	new_object_content = malloc(sizeof(*new_object_content));
	new_object = ft_lstnew(new_object_content);
	if (new_object == NULL || new_object_content == NULL)
	{
		free(new_object_content);
		free(new_object);
		ft_putstr_fd("Error\nFailed to allocate memory for objects\n",
			STDERR_FILENO);
		return (-1);
	}
	*new_object_content = object;
	ft_lstadd_front(object_list, new_object);
	return (0);
}
