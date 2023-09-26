/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_engine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 03:07:36 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/25 22:16:23 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlx.h"
#include "libft.h"

#include "engine.h"
#include "gui/box.h"

static void	destroy_images(t_engine *engine);

int	close_engine(t_engine *engine)
{
	if (engine->command_key_is_pressed)
		mlx_do_key_autorepeaton(engine->window.mlx);
	destroy_images(engine);
	free_scene(&engine->scene);
	camera_free(&engine->camera);
	free(engine->start_up_scene);
	destroy_mlx(engine);
	exit(0);
}

static void	destroy_images(t_engine *engine)
{
	destroy_t_image(&engine->window, &engine->main_image);
	destroy_t_image(&engine->window, &engine->ray_traced_image);
	destroy_t_image(&engine->window, &engine->bvh_image);
	free(engine->raytraced_pixels.data);
	engine->raytraced_pixels.data = NULL;
}
