/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_modification_box.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 00:04:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/23 23:02:38 by vfries           ###   ########.fr       */
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

typedef struct s_color_getter
{
	int	red;
	int	(*get_red)(float color, float x, float decal, float ratio);
	int	green;
	int	(*get_green)(float color, float x, float decal, float ratio);
	int	blue;
	int	(*get_blue)(float color, float x, float decal, float ratio);
}	t_color_getter;

typedef struct s_color_separator
{
	int	color_segment_width;
	int	max;
	int	previous_max;
}	t_color_separator;

//	init_color_picker/add_hover_color_circle.c
void	add_hover_color_circle(t_gui_box *self, t_vector2i offset,
			t_vector2i mouse_position);

//	init_color_picker/color_getter_functions.c
int		get_increasing_color(float color, float x, float decal,
			float ratio);
int		get_decreasing_color(float color, float x, float decal,
			float ratio);
int		get_base_color(float color, float x, float decal, float ratio);

//	init_color_picker/init_base_color_box.c
void	init_base_color_box(t_engine *minirt, t_gui_box *gui_box,
			t_gui_box *parent);

//	init_color_picker/init_color_picker_box.c
void	init_color_picker_box(t_engine *minirt, t_gui_box *gui_box,
			t_gui_box *parent);

//	init_color_picker/init_rgb_picker.c
void	init_rgb_picker(t_engine *minirt, t_gui_box *gui_box);

//	init_color_picker/on_clicks.c
void	base_color_picker_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data);
void	color_picker_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data);

//	init_object_modification_box.c
void	init_object_modification_gui_box(t_engine *minirt,
			t_gui_box *gui_box, const t_gui_box *main_gui_box);

#endif
