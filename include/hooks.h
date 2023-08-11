/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 10:45:44 by vfries            #+#    #+#             */
/*   Updated: 2023/04/15 10:46:06 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include "engine.h"
# include "gui/box.h"

int			button_release_handler(int button, int x, int y, t_engine *engine);
int			button_press_handler(int button, int x, int y, t_engine *engine);
int			key_press_handler(int key_code, t_engine *engine);
int			key_release_handler(int key_code, t_engine *engine);

void		redraw_icons(t_engine *engine, t_material material);
void		toggle_gui(t_gui *gui);
void		update_color_picker_color(t_gui *gui);

void		update_object_attributes_modification_box(t_engine *engine);
void		update_xyz_float_input_boxes(t_engine *engine,
				t_vector3f xyz, t_xyz_float_input_boxes *xyz_input_boxes);
void		update_xy_float_input_boxes(t_engine *engine,
				t_vector2f xy, t_xy_float_input_boxes *xy_input_boxes);
void		update_float_input_boxes(t_engine *engine);

int			get_transformations_boxes_index(
				t_gui_box *object_attribute_modification_box);
int			get_reflections_boxes_index(
				t_gui_box *object_attribute_modification_box);
int			get_texture_boxes_index(
				t_gui_box *object_attribute_modification_box);

void		init_cone_attributes_modification_box(t_engine *engine,
				t_gui_box *gui_box);
void		init_cylinder_attributes_modification_box(t_engine *engine,
				t_gui_box *gui_box);
void		init_light_attributes_modification_box(t_engine *engine,
				t_gui_box *gui_box);
void		init_plane_attributes_modification_box(t_engine *engine,
				t_gui_box *gui_box);
void		init_sphere_attributes_modification_box(t_engine *engine,
				t_gui_box *gui_box);

void		add_toggle_box(t_engine *engine, t_gui_box *gui_box, int *y,
				t_gui_box *parent);
void		add_x_y_box(t_engine *engine, t_gui_box *gui_box, int *i,
				t_gui_box *parent);
void		add_x_y_z_box(t_engine *engine, t_gui_box *gui_box, int *i,
				t_gui_box *parent);
void		draw_toggle_box(t_gui_box *gui_box, bool is_checkered);
int			get_attribute_box_size(void);
int			get_xyz_box_size(t_gui_box *attribute_box);
int			get_xy_box_size(t_gui_box *attribute_box);
int			get_normal_box_size(t_gui_box *attribute_box);
void		init_description_box(t_engine *engine, t_gui_box *gui_box,
				const char *description);

void		add_brightness_box(t_engine *engine, t_gui_box *gui_box, int *i,
				t_gui_box *parent);
void		add_cap_checkerboard_size_box(t_engine *engine, t_gui_box *gui_box,
				int *i, t_gui_box *parent);
void		add_outline_checkerboard_color_toggle_box(t_engine *engine,
				t_gui_box *gui_box, int *i, t_gui_box *parent);
void		add_cap_checkerboard_color_toggle_box(t_engine *engine,
				t_gui_box *gui_box, int *i, t_gui_box *parent);
void		add_outline_checkerboard_size_box(t_engine *engine,
				t_gui_box *gui_box, int *i, t_gui_box *parent);
void		add_delete_box(t_engine *engine, t_gui_box *gui_box,
				t_gui_box *parent);
void		add_height_box(t_engine *engine, t_gui_box *gui_box, int *i,
				t_gui_box *parent);
void		add_normal_box(t_engine *engine, t_gui_box *gui_box, int *i,
				t_gui_box *parent);
void		add_position_box(t_engine *engine, t_gui_box *gui_box, int *i,
				t_gui_box *parent);
void		add_radius_box(t_engine *engine, t_gui_box *gui_box, int *i,
				t_gui_box *parent);
void		add_reflection_box(t_engine *engine, t_gui_box *gui_box, int *i,
				t_gui_box *parent);
void		add_specular_reflection_box(t_engine *engine, t_gui_box *gui_box,
				int *i, t_gui_box *parent);

t_gui_box	*get_x_y_z_input_box(t_gui_box *gui_box, char type,
				char click_type);
t_gui_box	*get_x_y_input_box(t_gui_box *gui_box, char type, char click_type);

void		cap_checkerboard_size_input_box_x_on_click_plus(t_gui_box *self,
				t_engine *engine, t_click_data click_data);
void		cap_checkerboard_size_input_box_x_on_click_minus(
				t_gui_box *self, t_engine *engine, t_click_data click_data);
void		cap_checkerboard_size_input_box_x_on_click_text(t_gui_box *self,
				t_engine *engine, t_click_data click_data);
void		cap_checkerboard_size_input_box_y_on_click_plus(t_gui_box *self,
				t_engine *engine, t_click_data click_data);
void		cap_checkerboard_size_input_box_y_on_click_minus(
				t_gui_box *self, t_engine *engine, t_click_data click_data);
void		cap_checkerboard_size_input_box_y_on_click_text(t_gui_box *self,
				t_engine *engine, t_click_data click_data);

void		outline_checkerboard_size_input_box_x_on_click_plus(t_gui_box *self,
				t_engine *engine, t_click_data click_data);
void		outline_checkerboard_size_input_box_x_on_click_minus(
				t_gui_box *self, t_engine *engine, t_click_data click_data);
void		outline_checkerboard_size_input_box_x_on_click_text(t_gui_box *self,
				t_engine *engine, t_click_data click_data);
void		outline_checkerboard_size_input_box_y_on_click_plus(t_gui_box *self,
				t_engine *engine, t_click_data click_data);
void		outline_checkerboard_size_input_box_y_on_click_minus(
				t_gui_box *self, t_engine *engine, t_click_data click_data);
void		outline_checkerboard_size_input_box_y_on_click_text(t_gui_box *self,
				t_engine *engine, t_click_data click_data);

void		normal_input_box_x_on_click_plus(struct s_gui_box *self,
				t_engine *engine, t_click_data click_data);
void		normal_input_box_x_on_click_minus(struct s_gui_box *self,
				t_engine *engine, t_click_data click_data);
void		normal_input_box_x_on_click_text(t_gui_box *self, t_engine *engine,
				t_click_data click_data);
void		normal_input_box_y_on_click_plus(struct s_gui_box *self,
				t_engine *engine, t_click_data click_data);
void		normal_input_box_y_on_click_minus(struct s_gui_box *self,
				t_engine *engine, t_click_data click_data);
void		normal_input_box_y_on_click_text(t_gui_box *self, t_engine *engine,
				t_click_data click_data);
void		normal_input_box_z_on_click_plus(struct s_gui_box *self,
				t_engine *engine, t_click_data click_data);
void		normal_input_box_z_on_click_minus(struct s_gui_box *self,
				t_engine *engine, t_click_data click_data);
void		normal_input_box_z_on_click_text(t_gui_box *self, t_engine *engine,
				t_click_data click_data);


void		position_input_box_x_on_click_plus(struct s_gui_box *self,
				t_engine *engine, t_click_data click_data);
void		position_input_box_x_on_click_minus(struct s_gui_box *self,
				t_engine *engine, t_click_data click_data);
void		position_input_box_x_on_click_text(t_gui_box *self,
				t_engine *engine, t_click_data click_data);
void		position_input_box_y_on_click_plus(struct s_gui_box *self,
				t_engine *engine, t_click_data click_data);
void		position_input_box_y_on_click_minus(struct s_gui_box *self,
				t_engine *engine, t_click_data click_data);
void		position_input_box_y_on_click_text(t_gui_box *self,
				t_engine *engine, t_click_data click_data);
void		position_input_box_z_on_click_plus(struct s_gui_box *self,
				t_engine *engine, t_click_data click_data);
void		position_input_box_z_on_click_minus(struct s_gui_box *self,
				t_engine *engine, t_click_data click_data);
void		position_input_box_z_on_click_text(t_gui_box *self,
				t_engine *engine, t_click_data click_data);

#endif //HOOKS_H
