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

#include <stdbool.h>

#include "math/vector.h"
#include "box.h"

bool		mouse_is_hovering_box(const t_image *image_to_check_for_hover,
				t_vector2i mouse_position);
t_vector2i	get_mouse_position(t_gui_box *self, t_engine *engine,
				int x_offset, int y_offset);

int			create_n_horizontal_boxes(t_engine *engine, t_gui_box *gui_box,
				int n, int offset);

#endif