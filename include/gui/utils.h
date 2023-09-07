/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 02:01:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/11 02:01:00 by vfries           ###   ########lyon.fr   */
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

bool				is_mouse_hovering_box(const t_gui_box *gui_box,
						t_vector2i box_offset,
						const t_image *image_to_check_for_hover,
						t_vector2i mouse_position);
t_vector2i			get_mouse_position_in_box(const t_gui_box *self,
						t_vector2i box_offset, t_vector2i mouse_position);
t_vector2i			get_mouse_position(t_engine *engine);

t_boxes_to_create	get_boxes_size(const char *boxes_setup);
void				create_horizontal_boxes(t_engine *engine,
						t_gui_box *gui_box, const char *boxes_setup,
						int side_offset);
void				create_n_horizontal_boxes(t_engine *engine,
						t_gui_box *gui_box, int n, t_boxes_offsets offsets);
void				create_vertical_boxes(t_engine *engine, t_gui_box *gui_box,
						const char *boxes_setup, int side_offset);

void				update_float_input_box(const t_engine *engine, float f,
						t_gui_box *input_box);
void				create_float_input_box(t_engine *engine, t_gui_box *gui_box,
						t_float_input_box_on_click on_click);
void				draw_center_box_image(t_image *image);

void				draw_icon(t_image *image, int type,
						unsigned int background_color, t_material material);

void				draw_light_icon(t_image *image,
						unsigned int background_color, t_color color);
void				draw_top_rectangles(t_image *image, unsigned int color,
						float scale, t_vector2f offset);
void				draw_bottom_rectangles(t_image *image, unsigned int color,
						float scale, t_vector2f offset);
void				draw_side_rectangles(t_image *image, unsigned int color,
						float scale, t_vector2f offset);

t_vector2i			get_top_box_decal(const t_engine *engine,
						const t_gui_box *gui_box);
t_vector2i			get_right_box_decal(const t_engine *engine,
						const t_gui_box *gui_box);
t_vector2i			get_left_box_decal(const t_engine *engine,
						const t_gui_box *gui_box);

#endif
