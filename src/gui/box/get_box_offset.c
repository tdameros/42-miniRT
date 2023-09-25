/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_box_offset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:37:44 by vfries            #+#    #+#             */
/*   Updated: 2023/09/23 22:37:44 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui/box.h"

t_vector2i	get_box_offset(t_gui_box *box)
{
	t_vector2i	position;

	position = (t_vector2i){0, 0};
	box = box->parent;
	while (box != NULL)
	{
		position.x += box->position.x;
		position.y += box->position.y;
		box = box->parent;
	}
	return (position);
}
