/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen_shot_animation.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 03:58:02 by vfries            #+#    #+#             */
/*   Updated: 2023/09/24 04:00:53 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "mlx_wrapper.h"
#include "engine.h"

#define SCREEN_SHOT_ANIMATION_DURATION 250.f

void	render_screen_shot_animation(t_engine *engine)
{
	const uint64_t	current_time = ft_get_current_time_in_ms();
	const float		time_elapsed = current_time
		- engine->gui.screen_shot.last_screen_shot;
	int16_t			transparency;

	if (time_elapsed > SCREEN_SHOT_ANIMATION_DURATION)
		return ;
	if (time_elapsed < SCREEN_SHOT_ANIMATION_DURATION / 2.f)
		transparency = roundf((1.f - time_elapsed
					/ (SCREEN_SHOT_ANIMATION_DURATION / 2.f)) * 255.f);
	else
		transparency = roundf(
				(time_elapsed - SCREEN_SHOT_ANIMATION_DURATION / 2.f)
				/ (SCREEN_SHOT_ANIMATION_DURATION / 2.f) * 255.f);
	transparency = ft_clamp(transparency, 0, 255);
	change_image_color(&engine->gui.screen_shot.image,
		COLOR_WHITE | (transparency << 24));
	put_image(engine, &engine->gui.screen_shot.image, (t_vector2i){0, 0});
}
