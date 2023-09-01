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

# define OBJECT_ATTRIBUTE_BOX_OFFSET 8

# define OBJECT_ATTRIBUTE_BOX_XYZ_BOX_SIZE 2.5f
# define OBJECT_ATTRIBUTE_BOX_XY_BOX_SIZE 2.5f
# define OBJECT_ATTRIBUTE_BOX_NORMAL_BOX_SIZE 1.f

# define OBJECT_ATTRIBUTE_BOX_CATEGORY_OFFSET_SIZE .5f
# define OBJECT_ATTRIBUTE_BOX_CATEGORY_NB_OF_OFFSETS 3.f

# define OBJECT_ATTRIBUTE_BOX_TRANSFORMATION_NB_OF_XYZ_BOXES 2.f
# define OBJECT_ATTRIBUTE_BOX_TRANSFORMATION_NB_OF_XY_BOXES 0.f
# define OBJECT_ATTRIBUTE_BOX_TRANSFORMATION_NB_OF_NORMAL_BOXES 2.f

# define OBJECT_ATTRIBUTE_BOX_REFLECTION_NB_OF_XYZ_BOXES 0.f
# define OBJECT_ATTRIBUTE_BOX_REFLECTION_NB_OF_XY_BOXES 0.f
# define OBJECT_ATTRIBUTE_BOX_REFLECTION_NB_OF_NORMAL_BOXES 2.f

# define OBJECT_ATTRIBUTE_BOX_TEXTURE_NB_OF_XYZ_BOXES 0.f
# define OBJECT_ATTRIBUTE_BOX_TEXTURE_NB_OF_XY_BOXES 2.f
# define OBJECT_ATTRIBUTE_BOX_TEXTURE_NB_OF_NORMAL_BOXES 3.f

void	init_object_modification_gui_box(t_engine *minirt,
			t_gui_box *gui_box, const t_gui_box *main_gui_box);

void	init_rgb_picker(t_engine *minirt, t_gui_box *gui_box);
void	init_base_color_box(t_engine *minirt, t_gui_box *gui_box,
			t_gui_box *parent);
int		get_increasing_color(float color, float x, float decal,
			float ratio);
int		get_decreasing_color(float color, float x, float decal,
			float ratio);
int		get_base_color(float color, float x, float decal, float ratio);
void	init_color_picker_box(t_engine *minirt, t_gui_box *gui_box,
			t_gui_box *parent);
void	add_hover_color_circle(t_gui_box *self, t_vector2i offset,
			t_vector2i mouse_position);

#endif
