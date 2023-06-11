/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_modification_box.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 00:04:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/11 00:04:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_MODIFICATION_BOX_H
# define OBJECT_MODIFICATION_BOX_H

# include "engine.h"
# include "box.h"

int		init_object_modification_gui_box(t_engine *minirt,
			t_gui_box *gui_box, const t_gui_box *object_creation_gui_box);

int		init_rgb_picker(t_engine *minirt, t_gui_box *gui_box);
int		init_base_color_box(t_engine *minirt, t_gui_box *gui_box,
			t_gui_box *parent);
int		get_increasing_color(float color, float x, float decal,
			float ratio);
int		get_decreasing_color(float color, float x, float decal,
			float ratio);
int		get_base_color(float color, float x, float decal, float ratio);
int		init_color_picker_box(t_engine *minirt, t_gui_box *gui_box,
			t_gui_box *parent);
void	add_hover_color_circle(t_gui_box *self, t_engine *minirt,
			int x_offset, int y_offset);

void	init_object_attributes_modification_box(t_engine *engine,
			t_gui_box *gui_box);

#endif
