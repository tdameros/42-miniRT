/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_position_x_y_z_box.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:44:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/01 15:44:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "gui/box.h"

#define OFFSET 4

int	add_position_x_box(t_engine *engine, t_gui_box *gui_box, t_gui_box *parent)
{
	*gui_box = create_t_gui_box(engine, parent, \
		(t_vector2i){
			.x = OFFSET,
			.y = 0}, \
		(t_vector2i){
			.x = (parent->size.x - OFFSET * 4) / 3,
			.y = parent->size.y});
	if (errno == EINVAL)
		return (-1);
}

int	add_position_y_box(t_engine *engine, t_gui_box *gui_box, t_gui_box *parent)
{
	*gui_box = create_t_gui_box(engine, parent, \
		(t_vector2i){
			.x = (parent->size.x - OFFSET * 4) / 3 + OFFSET * 2,
			.y = 0}, \
		(t_vector2i){
			.x = (parent->size.x - OFFSET * 4) / 3,
			.y = parent->size.y});
	if (errno == EINVAL)
		return (-1);
}

int	add_position_z_box(t_engine *engine, t_gui_box *gui_box, t_gui_box *parent)
{
	*gui_box = create_t_gui_box(engine, parent, \
		(t_vector2i){
			.x = (parent->size.x - OFFSET * 4) / 3 * 2 + OFFSET * 3,
			.y = 0}, \
		(t_vector2i){
			.x = (parent->size.x - OFFSET * 4) / 3,
			.y = parent->size.y});
	if (errno == EINVAL)
		return (-1);
}
