/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_box_getters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 01:40:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/19 01:40:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gui/box.h"

t_image	*object_box_get_icon_image(const t_gui_box *object_box)
{
	return (&object_box->children.data->children.data[0].image);
}

t_image	*object_box_get_name_image(const t_gui_box *object_box)
{
	return (&object_box->children.data->children.data[2].children.data->image);
}
