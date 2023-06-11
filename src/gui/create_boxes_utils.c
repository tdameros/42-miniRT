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
		return ((t_boxes_to_create){NULL, 0});
	result.nb_of_boxes = ft_split_len(boxes);
	result.box_size = malloc(sizeof(*result.box_size) * result.nb_of_boxes);
	if (result.box_size == NULL)
	{
		ft_free_split(boxes);
		return ((t_boxes_to_create){NULL, 0});
	}
	i = result.nb_of_boxes;
	while (i--)
		result.box_size[i] = ft_atoi(boxes[i]);
	ft_free_split(boxes);
	return (result);
}

int	failed_to_create_all_boxes(t_engine *engine, t_gui_boxes *gui_boxes,
		size_t nb_of_boxes)
{
	while (nb_of_boxes--)
		destroy_t_image(&engine->window, &gui_boxes->data[nb_of_boxes].image);
	return (-1);
}
