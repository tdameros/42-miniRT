/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_n_horizontal_boxes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:52:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/01 17:52:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>

#include "gui/box.h"

static int	create_boxes(t_engine *engine, t_gui_box *gui_box, int n,
				int offset);
static void	free_gui_boxes_on_error(t_engine *engine, t_gui_boxes *gui_boxes,
				int nb);

int	create_n_horizontal_boxes(t_engine *engine, t_gui_box *gui_box, const int n,
		const int offset)
{
	if (n <= 0 || offset < 0 || gui_box == NULL
		|| (gui_box->size.x - (n + 1) * offset) / n <= 0)
	{
		ft_bzero(&gui_box->children, sizeof(gui_box->children));
		return (-1);
	}
	gui_box->children.data = malloc(sizeof(*gui_box->children.data) * n);
	if (gui_box->children.data == NULL)
		return (-1);
	gui_box->children.size = n;
	if (create_boxes(engine, gui_box, n, offset) >= 0)
		return (0);
	free(gui_box->children.data);
	ft_bzero(&gui_box->children, sizeof(gui_box->children));
	return (-1);
}

static int	create_boxes(t_engine *engine, t_gui_box *gui_box, int n,
				int offset)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		gui_box->children.data[i] = create_t_gui_box(engine, gui_box, \
			(t_vector2i){
				.x = (gui_box->size.x - (n + 1) * offset) / n * i \
					+ offset * (i + 1),
				.y = 0}, \
			(t_vector2i){
				.x = (gui_box->size.x - (n + 1) * offset) / n,
				.y = gui_box->size.y});
		if (errno == EINVAL || errno == ENOMEM)
		{
			free_gui_boxes_on_error(engine, &gui_box->children, i + 1);
			return (-1);
		}
	}
	return (0);
}

static void	free_gui_boxes_on_error(t_engine *engine, t_gui_boxes *gui_boxes,
				int nb)
{
	while (nb--)
		destroy_t_image(&engine->window, &gui_boxes->data[nb].image);
}
