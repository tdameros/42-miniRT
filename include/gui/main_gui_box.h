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

# define MENU_BOX_ICONS_COLOR 0x00666666

//	menu_box/init_export_box.c
void	init_export_box(t_engine *engine, t_gui_box *gui_box);

//	menu_box/init_menu_box.c
void	init_menu_gui_box(t_engine *engine, t_gui_box *gui_box,
			t_gui_box *parent);

//	menu_box/init_settings_icon.c
void	init_settings_icon(t_engine *engine, t_gui_box *gui_box);

//	object_creation_box/init_object_creation_box.c
void	init_object_creation_gui_box(t_engine *engine,
			t_gui_box *gui_box, t_gui_box *parent);

//	object_creation_box/light_create_on_click.c
void	light_create_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data);

//	object_creation_box/object_create_on_clicks.c
void	sphere_create_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data);
void	plane_create_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data);
void	cylinder_create_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data);
void	cone_create_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data);
void	mesh_create_on_click(t_gui_box *self, t_engine *engine,
			t_click_data click_data);

//	init_main_box.c
void	init_main_gui_box(t_engine *engine, t_gui_box *gui_box);

#endif
