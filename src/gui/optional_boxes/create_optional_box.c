/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_optional_box.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:25:30 by vfries            #+#    #+#             */
/*   Updated: 2023/09/01 18:25:31 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gui/box.h"

t_gui_box	create_optional_box(t_engine *engine, const t_gui_box *main_gui_box,
				const t_gui_box *object_list_box)
{
	const int			offset = object_list_box->position.y
		- (main_gui_box->position.y + main_gui_box->size.y);
	const t_vector2i	position = {object_list_box->position.x,
		object_list_box->position.y + object_list_box->size.y
		+ offset};
	const t_vector2i	size = {object_list_box->size.x, engine->window.size.y
		- position.y - offset};

	return (create_t_gui_box(engine, (t_gui_box_create){NULL,
			position, size, true}));
}
