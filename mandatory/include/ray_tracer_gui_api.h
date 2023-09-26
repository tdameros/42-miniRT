/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer_gui_api.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:57:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/31 14:57:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef RAY_TRACER_GUI_API_H
# define RAY_TRACER_GUI_API_H

# include "engine.h"

int			add_object(t_engine *engine, t_object object);
int			add_light(t_engine *engine, t_light light);
void		remove_object(t_engine *engine, size_t index);
void		remove_light(t_engine *engine, size_t index);

t_object	*get_clicked_object(t_engine *engine, int x, int y);

#endif
