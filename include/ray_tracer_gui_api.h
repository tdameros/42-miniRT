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

t_object	*get_clicked_object(t_engine *engine, int x, int y);

#endif
