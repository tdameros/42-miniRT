/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sphere_attributes_modification_box.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:31:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/01 11:31:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "gui/box.h"
#include "hooks.h"

typedef struct stest
{
	enum e_object_type	type;
	t_vector3f			position;
	t_color				albedo;
	float				radius;
	float				height;
	t_vector3f			normal;
	float				d;
}	ttest;

int	init_sphere_attributes_modification_box(t_engine *engine,
		t_gui_box *gui_box)
{
	int	i;

	gui_box->children.size = 1;
	gui_box->children.data = malloc(sizeof(*gui_box->children.data)
			* gui_box->children.size);
	i = 0;
	if (add_position_box(engine, gui_box->children.data, &i, gui_box))
		return (-1);
//	if (add_radius_box(engine, gui_box->children.data + 1, &i, gui_box))
//		return (-1); // TODO free previous
	return (0);
}
