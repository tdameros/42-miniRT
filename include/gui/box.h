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

typedef struct s_gui_box
{
	struct s_gui_box	*parent;
	t_vector2i			position;
	t_vector2i			size;
	t_image				image;
	t_image				on_hover_image;
	void				(*draw)(struct s_gui_box *self, t_engine *engine, \
							int x_offset, int y_offset);
	void				(*on_click)(struct s_gui_box *self, t_engine *engine, \
							int y, int x);
	t_gui_boxes			children;
}	t_gui_box;

t_gui_box	create_t_gui_box(t_engine *engine, t_gui_box *parent,
							  t_vector2i position, t_vector2i size);
void		destroy_t_gui_box(t_window *window, t_gui_box *gui_box);

void		default_gui_box_draw(t_gui_box *self, t_engine *engine,
								 int x_offset, int y_offset);
void		default_gui_box_on_click(t_gui_box *self, t_engine *engine, int y,
									 int x);

t_gui_box	*get_clicked_gui_box(t_gui_boxes gui_boxes, int *x, int *y);

#endif