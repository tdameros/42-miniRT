/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 03:05:27 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/25 17:58:50 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include "libft.h"
#include "mlx.h"

#include "mlx_wrapper.h"
#include "gui/init.h"
#include "events.h"
#include "parsing.h"
#include "hooks.h"
#include "render_frame.h"
#include "window.h"
#include "engine.h"
#include "font/render.h"

#ifndef DEFAULT_MAX_RESOLUTION_REDUCTION
# define DEFAULT_MAX_RESOLUTION_REDUCTION 21
#endif
#ifndef DEFAULT_MIN_RESOLUTION_REDUCTION
# define DEFAULT_MIN_RESOLUTION_REDUCTION 1
#endif
#ifndef DEFAULT_ANTIALIASING_VALUE
# define DEFAULT_ANTIALIASING_VALUE 1
#endif
#ifndef DEFAULT_BOUNCES_PER_PIXEL
# define DEFAULT_BOUNCES_PER_PIXEL 8
#endif

#define PATH_TO_FONT "assets/fonts/Envy Code R PR7/Envy Code R.ttf"

static void	init_rendering_settings(t_engine *engine);

int	init_engine(t_engine *engine, const char *start_up_scene,
		const char *path_to_minirt_binary)
{
	ft_bzero(engine, sizeof(t_engine));
	engine->start_up_scene = realpath(start_up_scene, NULL);
	if (engine->start_up_scene == NULL)
		return (-1);
	if (set_minirt_folder_as_current_working_directory(path_to_minirt_binary))
		return (-1);
	if (init_mlx(engine) < 0)
		return (-1);
	engine->window.is_focused = true;
	if (init_engine_images(engine) < 0)
		return (-1);
	init_rendering_settings(engine);
	if (get_font(&engine->gui.font, PATH_TO_FONT) < 0)
		return (-1);
	init_gui(engine);
	if (vectors_int_initialize(&engine->scene.plane_indexes, 5) < 0)
		return (-1);
	if (parse_scene(engine, engine->start_up_scene) < 0)
		return (-1);
	return (0);
}

static void	init_rendering_settings(t_engine *engine)
{
	engine->post_processing_effect = NO_EFFECT;
	engine->antialiasing = DEFAULT_ANTIALIASING_VALUE;
	engine->quality.max_reduction = DEFAULT_MAX_RESOLUTION_REDUCTION;
	engine->quality.min_reduction = DEFAULT_MIN_RESOLUTION_REDUCTION;
	engine->should_render_ray_tracing = true;
	engine->should_render_at_full_resolution = true;
	engine->scene.render_shadows = true;
	engine->scene.bounces_per_pixel = DEFAULT_BOUNCES_PER_PIXEL;
}
