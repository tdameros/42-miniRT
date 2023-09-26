/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 02:01:00 by vfries            #+#    #+#             */
/*   Updated: 2023/09/25 22:28:38 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>

# include "math/vector.h"
# include "box.h"

typedef struct s_float_input_box_on_click
{
	void	(*minus)(struct s_gui_box *, t_engine *, t_click_data);
	void	(*text_box)(struct s_gui_box *, t_engine *, t_click_data);
	void	(*plus)(struct s_gui_box *, t_engine *, t_click_data);
}	t_float_input_box_on_click;

typedef struct s_boxes_to_create
{
	int		*box_size;
	size_t	nb_of_boxes;
}	t_boxes_to_create;

typedef t_vector2i	t_boxes_offsets;

//	box/mouse_utils.c
bool				is_mouse_hovering_box(const t_gui_box *gui_box,
						t_vector2i box_offset,
						const t_image *image_to_check_for_hover,
						t_vector2i mouse_position);
t_vector2i			get_mouse_position_in_box(const t_gui_box *self,
						t_vector2i box_offset, t_vector2i mouse_position);

//	draw_icon/draw_light_icon/draw_bottom_rectangles.c
void				draw_bottom_rectangles(t_image *image, unsigned int color,
						float scale, t_vector2f offset);

//	draw_icon/draw_light_icon/draw_light_icon.c
void				draw_light_icon(t_image *image,
						unsigned int background_color, t_color color);

//	draw_icon/draw_light_icon/draw_sides_rectangles.c
void				draw_side_rectangles(t_image *image, unsigned int color,
						float scale, t_vector2f offset);

//	draw_icon/draw_light_icon/draw_top_rectangles.c
void				draw_top_rectangles(t_image *image, unsigned int color,
						float scale, t_vector2f offset);

//	draw_icon/get_object/get_mesh_object.c
t_object			get_mesh_object(const t_camera *camera,
						const t_object *object);

//	draw_icon/get_object/get_object.c
t_object			get_object(const t_object *base_object,
						t_engine *tmp_engine);

//	draw_icon/draw_icon.c
void				draw_icon(t_image *image, const t_object *object,
						const t_light *light, unsigned int background_color);

//	float_input_box/create_float_input_box.c
void				create_float_input_box(t_engine *engine, t_gui_box *gui_box,
						t_float_input_box_on_click on_click);

//	float_input_box/draw_float_input_box.c
void				draw_center_box_image(t_image *image);

//	float_input_box/update_float_input_box.c
void				update_float_input_box(const t_engine *engine, float f,
						t_gui_box *input_box);

//	create_boxes_utils.c
t_boxes_to_create	get_boxes_size(const char *boxes_setup);

//	create_horizontal_boxes.c
void				create_horizontal_boxes(t_engine *engine,
						t_gui_box *gui_box, const char *boxes_setup,
						int side_offset);

//	create_n_horizontal_boxes.c
void				create_n_horizontal_boxes(t_engine *engine,
						t_gui_box *gui_box, int n, t_boxes_offsets offsets);

//	create_vertical_boxes.c
void				create_vertical_boxes(t_engine *engine, t_gui_box *gui_box,
						const char *boxes_setup, int side_offset);

//	get_boxes_decal.c
t_vector2i			get_top_box_decal(const t_engine *engine,
						const t_gui_box *gui_box);
t_vector2i			get_right_box_decal(const t_engine *engine,
						const t_gui_box *gui_box);
t_vector2i			get_left_box_decal(const t_engine *engine,
						const t_gui_box *gui_box);

// write_message_to_screen
void				write_message_to_screen(t_engine *engine,
						const char *message);

#endif
