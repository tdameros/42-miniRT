/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_horizontal_boxes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:00:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/02 18:00:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "gui/box.h"

static int	*get_boxes_size(const char *boxes_setup, size_t *nb_of_boxes);
static int	create_boxes(t_engine *engine, t_gui_box *gui_box,
				const int *boxes_size, size_t box_count);
static int	failed_to_create_all_boxes(t_engine *engine, t_gui_boxes *gui_boxes,
				size_t nb_of_boxes);

///
/// \param engine
/// \param gui_box
/// \param boxes_setup "20 60 20" would mean having 3 boxes, 2 at the edges that
/// take 20 percent of available place, one in the center that takes 60 percent
/// of the available place. The sum of all numbers numbers needs to be > 0
///  && <= 100
/// \return
int	create_horizontal_boxes(t_engine *engine, t_gui_box *gui_box,
		const char *boxes_setup)
{
	size_t	nb_of_boxes;
	int		*boxes_size;

	boxes_size = get_boxes_size(boxes_setup, &nb_of_boxes);
	if (boxes_size == NULL)
	{
		ft_bzero(&gui_box->children, sizeof(gui_box->children));
		return (-1);
	}
	gui_box->children.data = malloc(sizeof(*gui_box->children.data)
			* nb_of_boxes);
	if (gui_box->children.data == NULL)
	{
		ft_bzero(&gui_box->children, sizeof(gui_box->children));
		return (free(boxes_size), -1);
	}
	gui_box->children.size = nb_of_boxes;
	if (create_boxes(engine, gui_box, boxes_size, nb_of_boxes) < 0)
	{
		free(gui_box->children.data);
		ft_bzero(&gui_box->children, sizeof(gui_box->children));
		free(boxes_size);
		return (-1);
	}
	return (free(boxes_size), 0);
}

static int	*get_boxes_size(const char *boxes_setup, size_t *nb_of_boxes)
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

static int	create_boxes(t_engine *engine, t_gui_box *gui_box,
				const int *boxes_size, size_t box_count)
{
	int		position;
	size_t	i;

	position = 0;
	i = -1;
	while (++i < box_count)
	{
		gui_box->children.data[i] = create_t_gui_box(engine, gui_box,
				(t_vector2i){\
					.x = position, \
					.y = 0}, \
				(t_vector2i){\
					.x = (i + 1 == box_count) \
							* (gui_box->size.x - position) \
						+ (i + 1 != box_count) \
							* (gui_box->size.x * (boxes_size[i] / 100.f)), \
					.y = gui_box->size.y});
		if (errno == EINVAL || errno == ENOMEM)
			return (failed_to_create_all_boxes(engine, &gui_box->children, i));
		position += gui_box->children.data[i].size.x;
	}
	return (0);
}

static int	failed_to_create_all_boxes(t_engine *engine, t_gui_boxes *gui_boxes,
				size_t nb_of_boxes)
{
	while (nb_of_boxes--)
		destroy_t_image(&engine->window, &gui_boxes->data[nb_of_boxes].image);
	return (-1);
}
