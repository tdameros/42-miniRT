/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 00:02:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/11 00:02:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include <sys/time.h>
# include <stdbool.h>

# include "gui/boxes.h"
# include "image.h"
# include "colors.h"
# include "object.h"
# include "light.h"
# include "font/rendering_structs.h"

typedef struct s_fps
{
	struct timeval	last_update;
	char			*fps_count;
	int				fps_nb;
}	t_fps;

typedef struct s_selected_object
{
	t_object	*object;
	t_light		*light;
}	t_selected_object;

typedef struct s_xyz_float_input_boxes
{
	struct s_gui_box	*x;
	struct s_gui_box	*y;
	struct s_gui_box	*z;
}	t_xyz_float_input_boxes;

typedef struct s_xy_float_input_boxes
{
	struct s_gui_box	*x;
	struct s_gui_box	*y;
}	t_xy_float_input_boxes;

typedef struct s_float_input_boxes
{
	struct s_gui_box		*brightness;
	struct s_gui_box		*height;
	t_xyz_float_input_boxes	normal;
	t_xyz_float_input_boxes	position;
	struct s_gui_box		*radius;
	struct s_gui_box		*reflection;
	struct s_gui_box		*specular_reflection;
	t_xy_float_input_boxes	checkered_pattern_size;
}	t_float_input_boxes;

typedef struct s_gui
{
	t_font				font;
	bool				is_hidden;
	uint64_t			start_animation_time;
	bool				hide_animation_finished;
	bool				should_show_gui_on_camera_lock;
	t_gui_boxes			gui_boxes;
	bool				color_picker_base_color_was_changed;
	t_color				color_picker_base_color;
	t_material			material_to_assign_to_new_objects;
	void				(*draw_gui_image)(t_image *destination, \
							const t_image *source, t_vector2i position);
	t_fps				fps;
	t_selected_object	selected_object;
	float				object_modification_amount;
	float				object_rotation_degrees;
	struct s_gui_box	*object_attributes_modification_box;
	struct s_gui_boxes	*object_creation_boxes;
	struct s_gui_box	*object_list_box;
	t_vector			object_boxes;
	t_vector			light_boxes;
	t_float_input_boxes	float_input_boxes;
	struct s_gui_box	*checkered_pattern_color_toggle_box;
	bool				color_being_changed_is_checked_pattern;
}	t_gui;

#endif
