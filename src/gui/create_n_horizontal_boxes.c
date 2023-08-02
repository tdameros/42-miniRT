/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_n_horizontal_boxes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:52:00 by vfries            #+#    #+#             */
/*   Updated: 2023/08/02 19:32:00 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>

#include "gui/box.h"
#include "gui/utils.h"

static void	create_boxes(t_engine *engine, t_gui_box *gui_box, int n,
				t_boxes_offsets offset);

void	create_n_horizontal_boxes(t_engine *engine, t_gui_box *gui_box,
			const int n, const t_boxes_offsets offset)
{
	if (n <= 0 || offset.x < 0 || offset.y < 0 || gui_box == NULL
		|| (gui_box->size.x - (n + 1) * offset.x) / n <= 0)
		ft_fatal_error("create_n_horizontal_boxes: invalid parameters");
	gui_box->children.data = ft_calloc(n, sizeof(*gui_box->children.data));
	if (gui_box->children.data == NULL)
		ft_fatal_error("create_n_horizontal_boxes: malloc error");
	gui_box->children.size = n;
	create_boxes(engine, gui_box, n, offset);
}

static void	create_boxes(t_engine *engine, t_gui_box *gui_box, int n,
				const t_boxes_offsets offset)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		gui_box->children.data[i] = create_t_gui_box(engine, \
			(t_gui_box_create){
				gui_box, \
				(t_vector2i){\
					.x = (gui_box->size.x - (n + 1) * offset.x) / n * i \
						+ offset.x * (i + 1), \
					.y = offset.y}, \
				(t_vector2i){\
					.x = (gui_box->size.x - (n + 1) * offset.x) / n, \
					.y = gui_box->size.y - offset.y * 2},
				false});
	}
}
