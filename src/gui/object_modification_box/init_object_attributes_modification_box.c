/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_object_attributes_modification_box.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:41:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/01 10:41:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "gui/box.h"

static void	object_attributes_modification_box_draw(t_gui_box *self,
				t_engine *engine, int x_offset, int y_offset);

int	init_object_attributes_modification_box(t_engine *engine,
		t_gui_box *gui_box, t_gui_box *parent)
{
	*gui_box = create_t_gui_box(engine, parent, \
		(t_vector2i){
			.x = 8,
			.y = 8}, \
		(t_vector2i){
			.x = parent->size.x - 16,
			.y = parent->size.y - parent->size.y / 6 - 16});
	if (errno == EINVAL || errno == ENOMEM)
	{
		ft_bzero(gui_box, sizeof(*gui_box));
		return (-1);
	}
	gui_box->draw = &object_attributes_modification_box_draw;
	engine->gui.object_attributes_modification_box = gui_box;
	return (0);
}

static void	object_attributes_modification_box_draw(t_gui_box *self,
				t_engine *engine, int x_offset, int y_offset)
{
	size_t	i;

	i = self->children.size;
	while (i--)
		if (self->children.data[i].draw != NULL)
			self->children.data[i].draw(self->children.data + i, engine,
				x_offset + self->position.x, y_offset + self->position.y);
}
