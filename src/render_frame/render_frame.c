/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:12:50 by vfries            #+#    #+#             */
/*   Updated: 2023/09/25 19:03:28 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <math.h>

#include "mlx.h"
#include "libft.h"

#include "engine.h"
#include "render_frame.h"
#include "ray_tracer/render.h"
#include "events.h"
#include "hooks.h"
#include "mlx_wrapper.h"
#include "object.h"
#include "interpolater.h"
#include "draw.h"

#define FPS_GOAL 45.f
#define FRAME_BEFORE_ADAPTION 20
#define DEFAULT_INCREMENTER_VALUE 2

static void			render_minirt_raytracing(t_engine *engine);

int	render_frame(t_engine *engine)
{
	render_minirt_raytracing(engine);
	put_image(engine, &engine->ray_traced_image, (t_vector2i){0, 0});
	if (IS_LINUX)
		mlx_put_image_to_window(engine->window.mlx, engine->window.window,
			engine->main_image.data, 0, 0);
	return (0);
}

static void	render_minirt_raytracing(t_engine *engine)
{
	render_anti_aliased_raytracing(engine);
	put_raytraced_pixels_to_raytraced_image(engine);
}
