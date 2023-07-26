/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_x_y_input_box.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:23:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/23 19:23:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "gui/box.h"

static int8_t	get_input_box_index(char type);
static int8_t	get_specific_index(char click_type);

///
/// \param gui_box
/// \param type x or y
/// \param click_type - to get the minus box, + to get the plus box,
/// t to get the text box, d to get the box on which x or y is written,
/// b to get the whole float input box (without the box on which x or y is
/// written)
/// \return NULL if type / click type in incorrect. Returns pointer to the
/// requested gui box otherwise
t_gui_box	*get_x_y_input_box(t_gui_box *gui_box, char type, char click_type)
{
	const int8_t	input_box_index = get_input_box_index(type);
	const int8_t	specific_index = get_specific_index(click_type);

	if (input_box_index < 0
		|| (specific_index < 0 && click_type != 'b' && click_type != 'd'))
		return (NULL);
	if (click_type == 'd')
		return (gui_box->children.data[1].children.data[input_box_index] \
			.children.data);
	if (click_type == 'b')
		return (gui_box->children.data[1].children.data[input_box_index] \
			.children.data + 1);
	return (gui_box->children.data[1].children.data[input_box_index] \
			.children.data[1].children.data + specific_index);
}

static int8_t	get_input_box_index(char type)
{
	if (type == 'x')
		return (0);
	if (type == 'y')
		return (1);
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
