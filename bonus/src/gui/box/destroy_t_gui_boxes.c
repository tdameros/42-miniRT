/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_t_gui_boxes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:37:40 by vfries            #+#    #+#             */
/*   Updated: 2023/09/23 22:37:40 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "gui/box.h"

void	destroy_t_gui_boxes(t_window *window, t_gui_boxes *gui_boxes)
{
	if (gui_boxes->data != NULL)
	{
		while (gui_boxes->size--)
			destroy_t_gui_box(window, gui_boxes->data + gui_boxes->size);
		free(gui_boxes->data);
		gui_boxes->data = NULL;
	}
	gui_boxes->size = 0;
}
