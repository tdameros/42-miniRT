/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_list_box.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 11:50:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/30 17:44:47 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_LIST_BOX_H
# define OBJECT_LIST_BOX_H

# include "engine.h"
# include "gui/box.h"

# define OBJECT_LIST_OFFSET 4
# define OBJECT_LIST_SUB_BOX_SIZE 50
# define OBJECT_LIST_SUB_BOX_BOXES "25 1 74"


void	init_object_list_box(t_engine *engine, t_gui_box *gui_box,
			const t_gui_box *main_gui_box,
			const t_gui_box *object_modification_gui_box);

void	object_list_gui_box_draw(t_gui_box *self, t_engine *engine,
			t_draw_data draw_data);
void	object_list_gui_box_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data);
size_t	get_selected_object_index(t_gui_box *self, t_engine *engine,
			t_vector2i click_position);

void	create_object_gui_box(t_engine *engine, t_gui_box *gui_box,
			const t_object *object);
void	create_light_gui_box(t_engine *engine, t_gui_box *gui_box,
			const t_light *light);

t_image	*object_box_get_icon_image(const t_gui_box *object_box);

void	update_object_list_icons(t_engine *engine);

#endif
