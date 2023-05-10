/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_modification_box.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 00:04:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/11 00:04:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_MODIFICATION_BOX_H
# define OBJECT_MODIFICATION_BOX_H

# define ICON_BOX_SEPARATOR 4
# define ICON_BOX_COLOR 0x40404040
# define ICON_BOX_ROUNDING_RADIUS 20

bool			mouse_is_hovering_box(t_gui_box *self,
									  t_vector2i mouse_position);
t_vector2i	get_mouse_position(t_gui_box *self, t_minirt *minirt,
								 int x_offset, int y_offset);


int				init_object_modification_gui_box(t_minirt *minirt,
													t_gui_box *gui_box, const t_gui_box *object_creation_gui_box);

int				init_rgb_picker(t_minirt *minirt, t_gui_box *gui_box,
								   t_gui_box *parent);
int				init_base_color_box(t_minirt *minirt, t_gui_box *gui_box,
									   t_gui_box *parent);
int				get_increasing_color(double color, double x, double decal,
										double ratio);
int				get_decreasing_color(double color, double x, double decal,
										double ratio);
int				get_base_color(double color, double x, double decal, double ratio);
int				init_color_picker_box(t_minirt *minirt, t_gui_box *gui_box,
										 t_gui_box *parent);
void			add_hover_color_circle(t_gui_box *self, t_minirt *minirt,
									   int x_offset, int y_offset);


#endif
