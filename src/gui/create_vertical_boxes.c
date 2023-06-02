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
#include "gui/utils.h"

static int	create_boxes(t_engine *engine, t_gui_box *gui_box,
				const int *boxes_size, size_t box_count);

///
/// \param engine
/// \param gui_box
/// \param boxes_setup "20 60 20" would mean having 3 boxes, 2 at the edges that
/// take 20 percent of available place, one in the center that takes 60 percent
/// of the available place. The sum of all numbers numbers needs to be > 0
///  && <= 100
/// \return
int	create_vertical_boxes(t_engine *engine, t_gui_box *gui_box,
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
					.x = 0, \
					.y = position}, \
				(t_vector2i){\
					.x = gui_box->size.x, \
					.y = (i + 1 == box_count) \
							* (gui_box->size.y - position) \
						+ (i + 1 != box_count) \
							* (gui_box->size.y * (boxes_size[i] / 100.f))});
		if (errno == EINVAL || errno == ENOMEM)
			return (failed_to_create_all_boxes(engine, &gui_box->children, i));
		position += gui_box->children.data[i].size.y;
	}
	return (0);
}
