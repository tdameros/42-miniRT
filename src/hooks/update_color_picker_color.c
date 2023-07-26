/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_color_picker_color.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 01:03:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/19 01:03:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gui/gui.h"

void	update_color_picker_color(t_gui *gui)
{
	if (gui->selected_object.object != NULL)
	{
		gui->color_picker_base_color_was_changed = true;
		gui->color_picker_base_color = vector3f_multiply(
				gui->selected_object.object->material.albedo, 255.f);
	}
	else if (gui->selected_object.light != NULL)
	{
		gui->color_picker_base_color_was_changed = true;
		gui->color_picker_base_color = vector3f_multiply(
				gui->selected_object.light->color, 255.f);
	}
}
