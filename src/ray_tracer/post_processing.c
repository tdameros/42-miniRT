/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:08:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/05 18:08:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "math/vector.h"
#include "engine.h"

t_vector3f	calculate_post_processing_color(const t_engine *engine,
											t_vector3f color)
{
	float	new_color;

	if (engine->is_black_and_white_render)
	{
		new_color = 0.299f * color.x + 0.587f * color.y + 0.114f * color.z;
		color = (t_vector3f){new_color, new_color, new_color};
	}
	return (color);
}