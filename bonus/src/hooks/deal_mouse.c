/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 07:12:37 by vfries            #+#    #+#             */
/*   Updated: 2023/09/24 07:13:33 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "mlx_wrapper.h"

int	deal_mouse(t_engine *engine)
{
	t_vector2i	mouse_position;
	float		yaw_delta;
	float		pitch_delta;

	if (engine->camera.lock == false && engine->window.is_focused)
	{
		mouse_position = engine->mouse_position;
		yaw_delta = (engine->previous_mouse_position.x - mouse_position.x)
			* engine->camera.rotation_speed;
		pitch_delta = (engine->previous_mouse_position.y - mouse_position.y)
			* engine->camera.rotation_speed;
		if (yaw_delta != 0 || pitch_delta != 0)
		{
			camera_rotate_up(&engine->camera, pitch_delta);
			camera_rotate_left(&engine->camera, yaw_delta);
		}
		else
			return (0);
		mouse_move(engine, (t_vector2i){engine->ray_traced_image.width / 2,
			engine->ray_traced_image.height / 2});
		engine->previous_mouse_position = (t_vector2i){
			engine->window.size.x / 2, engine->window.size.y / 2};
		return (1);
	}
	return (0);
}
