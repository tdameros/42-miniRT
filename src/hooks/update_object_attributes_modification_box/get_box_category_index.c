/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_box_category_index.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:49:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/19 17:49:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gui/box.h"
#include "gui/object_modification_box.h"

int	get_transformations_boxes_index(
		t_gui_box *object_attribute_modification_box)
{
	(void)object_attribute_modification_box;
	return (0);
}

int	get_reflections_boxes_index(t_gui_box *object_attribute_modification_box)
{
	const float	size_of_transformation_xyz_boxes
		= OBJECT_ATTRIBUTE_BOX_TRANSFORMATION_NB_OF_XYZ_BOXES \
			* OBJECT_ATTRIBUTE_BOX_XYZ_BOX_SIZE;
	const float	size_of_transformation_normal_boxes
		= OBJECT_ATTRIBUTE_BOX_TRANSFORMATION_NB_OF_NORMAL_BOXES \
			* OBJECT_ATTRIBUTE_BOX_NORMAL_BOX_SIZE;
	const float	size_of_transformation = size_of_transformation_xyz_boxes
		+ size_of_transformation_normal_boxes
		+ OBJECT_ATTRIBUTE_BOX_CATEGORY_OFFSET_SIZE;

	return (object_attribute_modification_box->size.y
		* (size_of_transformation / OBJECT_ATTRIBUTE_BOX_TOTAL_SIZE));
}

int	get_texture_boxes_index(t_gui_box *object_attribute_modification_box)
{
	const float	size_of_reflection_xyz_boxes
		= OBJECT_ATTRIBUTE_BOX_REFLECTION_NB_OF_XYZ_BOXES \
			* OBJECT_ATTRIBUTE_BOX_XYZ_BOX_SIZE;
	const float	size_of_reflection_boxes
		= OBJECT_ATTRIBUTE_BOX_REFLECTION_NB_OF_NORMAL_BOXES \
			* OBJECT_ATTRIBUTE_BOX_NORMAL_BOX_SIZE;
	const float	size_of_reflection = size_of_reflection_xyz_boxes
		+ size_of_reflection_boxes + OBJECT_ATTRIBUTE_BOX_CATEGORY_OFFSET_SIZE;
	const float	size_of_reflection_in_pixels
		= object_attribute_modification_box->size.y \
			* (size_of_reflection / OBJECT_ATTRIBUTE_BOX_TOTAL_SIZE);

	return (size_of_reflection_in_pixels
		+ get_reflections_boxes_index(object_attribute_modification_box));
}
