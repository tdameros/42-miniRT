/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_x_y_z_input_box.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 05:28:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/03 05:28:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "gui/box.h"

static int8_t	get_input_box_index(char type);
static int8_t	get_specific_index(char click_type);

t_gui_box	*get_x_y_z_input_box(t_gui_box *gui_box, char type, char click_type)
{
	const int8_t	input_box_index = get_input_box_index(type);
	const int8_t	specific_index = get_specific_index(click_type);

	if (input_box_index < 0 || specific_index < 0)
		return (NULL);
	return (gui_box->children.data[1].children.data[input_box_index] \
			.children.data[1].children.data + specific_index);
}

static int8_t	get_input_box_index(char type)
{
	if (type == 'x')
		return (0);
	if (type == 'y')
		return (1);
	if (type == 'z')
		return (2);
	return (-1);
}

static int8_t	get_specific_index(char click_type)
{
	if (click_type == '-')
		return (0);
	if (click_type == 't')
		return (1);
	if (click_type == '+')
		return (2);
	return (-1);
}

