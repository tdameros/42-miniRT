/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_boxes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 23:02:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/02 23:02:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "gui/box.h"
#include "gui/utils.h"

t_boxes_to_create	get_boxes_size(const char *boxes_setup)
{
	char				**boxes;
	t_boxes_to_create	result;
	size_t				i;

	boxes = ft_split(boxes_setup, ' ');
	if (boxes == NULL)
		ft_fatal_error("get_boxes_size: ft_split failed");
	result.nb_of_boxes = ft_split_len(boxes);
	result.box_size = malloc(sizeof(*result.box_size) * result.nb_of_boxes);
	if (result.box_size == NULL)
		ft_fatal_error("get_boxes_size: malloc failed");
	i = result.nb_of_boxes;
	while (i--)
		result.box_size[i] = ft_atoi(boxes[i]);
	ft_free_split(boxes);
	return (result);
}
