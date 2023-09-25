/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 10:45:34 by vfries            #+#    #+#             */
/*   Updated: 2023/09/24 07:37:06 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_FRAME_H
# define RENDER_FRAME_H

# include "engine.h"

int		render_frame(t_engine *minirt);

void	render_user_interface(t_engine *engine, uint64_t start_time);
void	render_message(t_engine *engine);
void	render_screen_shot_animation(t_engine *engine);

void	put_raytraced_pixels_to_raytraced_image(t_engine *engine);
void	print_fps_counter(t_engine *engine, struct timeval start_time);
void	update_placed_object_position(t_engine *engine);
void	update_scene(t_engine *engine, const uint64_t start_time);

#endif
