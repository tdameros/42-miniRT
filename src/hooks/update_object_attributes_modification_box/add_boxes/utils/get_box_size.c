/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_box_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 22:28:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/20 22:28:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gui/box.h"
#include "gui/object_modification_box.h"

float	get_attribute_box_size(void)
{
	return (OBJECT_ATTRIBUTE_BOX_NORMAL_BOX_SIZE
		+ OBJECT_ATTRIBUTE_BOX_TRANSFORMATION_NB_OF_XYZ_BOXES \
			* OBJECT_ATTRIBUTE_BOX_XYZ_BOX_SIZE
		+ OBJECT_ATTRIBUTE_BOX_TRANSFORMATION_NB_OF_XY_BOXES \
			* OBJECT_ATTRIBUTE_BOX_XY_BOX_SIZE
		+ OBJECT_ATTRIBUTE_BOX_TRANSFORMATION_NB_OF_NORMAL_BOXES \
			* OBJECT_ATTRIBUTE_BOX_NORMAL_BOX_SIZE
		+ OBJECT_ATTRIBUTE_BOX_REFLECTION_NB_OF_XYZ_BOXES \
			* OBJECT_ATTRIBUTE_BOX_XYZ_BOX_SIZE
		+ OBJECT_ATTRIBUTE_BOX_REFLECTION_NB_OF_XY_BOXES \
			* OBJECT_ATTRIBUTE_BOX_XY_BOX_SIZE
		+ OBJECT_ATTRIBUTE_BOX_REFLECTION_NB_OF_NORMAL_BOXES \
			* OBJECT_ATTRIBUTE_BOX_NORMAL_BOX_SIZE
		+ OBJECT_ATTRIBUTE_BOX_TEXTURE_NB_OF_XYZ_BOXES \
			* OBJECT_ATTRIBUTE_BOX_XYZ_BOX_SIZE
		+ OBJECT_ATTRIBUTE_BOX_TEXTURE_NB_OF_XY_BOXES \
			* OBJECT_ATTRIBUTE_BOX_XY_BOX_SIZE
		+ OBJECT_ATTRIBUTE_BOX_TEXTURE_NB_OF_NORMAL_BOXES \
			* OBJECT_ATTRIBUTE_BOX_NORMAL_BOX_SIZE
		+ OBJECT_ATTRIBUTE_BOX_CATEGORY_NB_OF_OFFSETS \
			* OBJECT_ATTRIBUTE_BOX_CATEGORY_OFFSET_SIZE);
}

int	get_xyz_box_size(t_gui_box *attribute_box)
{
	return (attribute_box->size.y * (OBJECT_ATTRIBUTE_BOX_XYZ_BOX_SIZE
			/ get_attribute_box_size()) - OBJECT_ATTRIBUTE_BOX_OFFSET);
}

int	get_xy_box_size(t_gui_box *attribute_box)
{
	return (attribute_box->size.y * (OBJECT_ATTRIBUTE_BOX_XY_BOX_SIZE
			/ get_attribute_box_size()) - OBJECT_ATTRIBUTE_BOX_OFFSET);
}

int	get_normal_box_size(t_gui_box *attribute_box)
{
	return (attribute_box->size.y * (OBJECT_ATTRIBUTE_BOX_NORMAL_BOX_SIZE
			/ get_attribute_box_size()) - OBJECT_ATTRIBUTE_BOX_OFFSET);
}
