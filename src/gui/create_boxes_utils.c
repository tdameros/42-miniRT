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

int	*get_boxes_size(const char *boxes_setup, size_t *nb_of_boxes)
{
	char	**boxes;
	int		*result;
	size_t	i;

	boxes = ft_split(boxes_setup, ' ');
	if (boxes == NULL)
		return (NULL);
	*nb_of_boxes = ft_split_len(boxes);
	result = malloc(sizeof(*result) * *nb_of_boxes);
	if (result == NULL)
		return (ft_free_split(boxes), NULL);
	i = *nb_of_boxes;
	while (i--)
		result[i] = ft_atoi(boxes[i]);
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
