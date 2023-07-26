/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 00:01:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/11 00:01:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOX_H
# define BOX_H

# include "math/vector.h"
# include "gui/boxes.h"
# include "image.h"
# include "engine.h"

typedef struct s_draw_data
{
	t_vector2i	offset;
	t_vector2i	mouse_position;
}	t_draw_data;

typedef struct s_click_data
{
	t_vector2i	click_position;
	int			button;
}	t_click_data;

typedef struct s_gui_box
{
	struct s_gui_box	*parent;
	t_vector2i			position;
	t_vector2i			size;
	t_image				image;
	t_image				on_hover_image;
	void				(*draw)(struct s_gui_box *self, t_engine *engine, \
							t_draw_data draw_data);
	void				(*on_click)(struct s_gui_box *self, t_engine *engine, \
							t_click_data click_data);
	t_gui_boxes			children;
	int					scroll;
}	t_gui_box;

typedef struct s_gui_box_create
{
	t_gui_box	*parent;
	t_vector2i	position;
	t_vector2i	size;
	bool		should_create_an_image;
}	t_gui_box_create;

t_gui_box	create_t_gui_box(t_engine *engine, t_gui_box_create args);
void		destroy_t_gui_box(t_window *window, t_gui_box *gui_box);

void		default_gui_box_draw(struct s_gui_box *self, t_engine *engine,
				t_draw_data draw_data);
void		default_gui_box_on_click(t_gui_box *self, t_engine *minirt,
				t_click_data click_data);

t_gui_box	*get_clicked_gui_box(t_gui_boxes gui_boxes, int *x, int *y);

#endif
