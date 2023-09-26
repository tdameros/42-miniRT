/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_message.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 03:51:34 by vfries            #+#    #+#             */
/*   Updated: 2023/09/24 03:56:42 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "engine.h"
#include "gui/gui.h"
#include "mlx_wrapper.h"

static int16_t		get_message_transparency(const t_message *message,
						float time_elapsed);
static void			update_message_image_to_display(t_message *message,
						int16_t transparency);

void	render_message(t_engine *engine)
{
	t_message		*message;
	const float		time_elapsed = ft_get_current_time_in_ms()
		- engine->gui.message.animation_start_time_ms;
	int16_t			transparency;

	message = &engine->gui.message;
	if (time_elapsed > message->time_to_appear_ms + message->time_to_display_ms
		+ message->time_to_disappear_ms)
		return ;
	transparency = get_message_transparency(message, time_elapsed);
	update_message_image_to_display(message, transparency);
	put_image(engine, &message->image_to_display,
		(t_vector2i){0, message->y_position});
}

static int16_t	get_message_transparency(const t_message *message,
					const float time_elapsed)
{
	if (time_elapsed < message->time_to_appear_ms)
		return (roundf((1.f - time_elapsed
					/ (message->time_to_appear_ms)) * 255.f));
	if (time_elapsed > message->time_to_appear_ms
		+ message->time_to_display_ms)
		return (roundf((time_elapsed - message->time_to_appear_ms
					- message->time_to_display_ms)
				/ message->time_to_display_ms * 255.f));
	return (0);
}

static void	update_message_image_to_display(t_message *message,
				const int16_t transparency)
{
	const unsigned int	*original;
	unsigned int		*display;
	int16_t				pixel_transparency;

	original = message->image_with_message.address;
	display = message->image_to_display.address;
	while (display < message->image_to_display.limit)
	{
		pixel_transparency = transparency + get_transparency(*original);
		pixel_transparency = ft_clamp(pixel_transparency, 0, 255);
		*display = (*original & 0x00FFFFFF) | (pixel_transparency << 24);
		original++;
		display++;
	}
}
