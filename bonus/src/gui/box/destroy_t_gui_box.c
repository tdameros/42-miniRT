/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_t_gui_box.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:22:29 by vfries            #+#    #+#             */
/*   Updated: 2023/07/30 18:22:30 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlx.h"

#include "window.h"
#include "gui/box.h"

void	destroy_t_gui_box(t_window *window, t_gui_box *gui_box)
{
	if (gui_box->image.data != NULL)
		mlx_destroy_image(window->mlx, gui_box->image.data);
	gui_box->image = (t_image){0};
	if (gui_box->on_hover_image.data != NULL)
		mlx_destroy_image(window->mlx, gui_box->on_hover_image.data);
	gui_box->on_hover_image = (t_image){0};
	destroy_t_gui_boxes(window, &gui_box->children);
}
