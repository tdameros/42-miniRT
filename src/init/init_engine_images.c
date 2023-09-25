/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_engine_images.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:01:28 by vfries            #+#    #+#             */
/*   Updated: 2023/09/25 17:03:10 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	init_engine_images(t_engine *engine)
{
	init_image(&engine->ray_traced_image, &engine->window,
		engine->window.size.x, engine->window.size.y);
	init_image(&engine->bvh_image, &engine->window,
		engine->window.size.x, engine->window.size.y);
	engine->raytraced_pixels.data = malloc(\
		sizeof(*engine->raytraced_pixels.data) * engine->ray_traced_image.size);
	if (engine->raytraced_pixels.data == NULL)
		return (-1);
	engine->raytraced_pixels.size = engine->ray_traced_image.size;
	engine->raytraced_pixels.width = engine->ray_traced_image.width;
	engine->raytraced_pixels.height = engine->ray_traced_image.height;
	init_image(&engine->main_image, &engine->window, engine->window.size.x,
		engine->window.size.y);
	init_image(&engine->gui.screen_shot.image, &engine->window,
		engine->window.size.x, engine->window.size.y);
	return (0);
}
