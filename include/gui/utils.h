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
	void	(*minus)(struct s_gui_box *, t_engine *, int, int);
	void	(*text_box)(struct s_gui_box *, t_engine *, int, int);
	void	(*plus)(struct s_gui_box *, t_engine *, int, int);
}	t_float_input_box_on_click;

typedef struct s_boxes_to_create
{
	int		*box_size;
	size_t	nb_of_boxes;
}	t_boxes_to_create;

typedef struct s_boxes_offsets
{
	int	x;
	int	y;
}	t_boxes_offsets;

bool				mouse_is_hovering_box(
						const t_image *image_to_check_for_hover,
						t_vector2i mouse_position);
t_vector2i			get_mouse_position_in_box(t_gui_box *self, t_engine *engine,
						int x_offset, int y_offset);
t_vector2i			get_mouse_position(t_engine *engine);

t_boxes_to_create	get_boxes_size(const char *boxes_setup);
int					failed_to_create_all_boxes(t_engine *engine,
						t_gui_boxes *gui_boxes, size_t nb_of_boxes);
int					create_horizontal_boxes(t_engine *engine,
						t_gui_box *gui_box, const char *boxes_setup,
						int side_offset);
int					create_n_horizontal_boxes(t_engine *engine,
						t_gui_box *gui_box, int n, t_boxes_offsets offsets);
int					create_vertical_boxes(t_engine *engine, t_gui_box *gui_box,
						const char *boxes_setup, int side_offset);

int					create_float_input_box(t_engine *engine, t_gui_box *gui_box,
						t_float_input_box_on_click on_click);

#endif
