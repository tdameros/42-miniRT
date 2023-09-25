/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_object_list_icons.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 23:29:02 by vfries            #+#    #+#             */
/*   Updated: 2023/09/23 23:29:03 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gui/utils.h"
#include "gui/object_list_box.h"

void	update_object_list_icons(t_engine *engine)
{
	t_gui_box		*object_box;
	t_image			*icon_image;
	const t_object	*object;
	const t_light	*light;
	size_t			i;

	i = engine->scene.lights.length;
	while (i--)
	{
		object_box = &((t_gui_box *)engine->gui.light_boxes.data)[i];
		icon_image = object_box_get_icon_image(object_box);
		light = &engine->scene.lights.data[i];
		draw_icon(icon_image, NULL, light, COLOR_TRANSPARENT);
	}
	i = engine->scene.objects.length;
	while (i--)
	{
		object_box = &((t_gui_box *)engine->gui.object_boxes.data)[i];
		icon_image = object_box_get_icon_image(object_box);
		object = &engine->scene.objects.data[i];
		draw_icon(icon_image, object, NULL, COLOR_TRANSPARENT);
	}
}
