/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_gui_box.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 23:59:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/10 23:59:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_GUI_BOX_H
# define MAIN_GUI_BOX_H

int		init_main_gui_box(t_engine *engine, t_gui_box *gui_box);
int		init_object_creation_gui_box(t_engine *engine,
			t_gui_box *gui_box, t_gui_box *parent);
int		init_menu_gui_box(t_engine *engine, t_gui_box *gui_box,
			t_gui_box *parent);
void	icon_box_draw_method(t_gui_box *self, t_engine *engine,
			int x_offset, int y_offset);
void	init_settings_icon(t_gui_box *gui_box);

void	sphere_create_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data);
void	plane_create_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data);
void	cylinder_create_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data);
void	cone_create_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data);
void	light_create_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data);

#endif
