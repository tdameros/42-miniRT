/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 03:05:59 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/24 09:27:06 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

#include "engine.h"

#ifdef __APPLE__

void	put_image(t_engine *engine, t_image *image, t_vector2i position)
{
	mlx_put_image_to_window(engine->window.mlx, engine->window.window,
		image->data, position.x, position.y);
}
#endif
#ifdef __linux__

void	put_image(t_engine *engine, t_image *image, t_vector2i position)
{
	engine->gui.draw_gui_image(&engine->main_image, image, position);
}
#endif
