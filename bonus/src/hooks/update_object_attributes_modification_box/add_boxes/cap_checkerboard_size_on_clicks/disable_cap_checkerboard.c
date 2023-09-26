/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disable_cap_checkerboard.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 09:07:01 by vfries            #+#    #+#             */
/*   Updated: 2023/09/24 09:25:02 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "object.h"
#include "hooks.h"

void	disable_cap_checkerboard(t_engine *engine, t_object *object)
{
	object->material.textures.cap.texture_type = NONE;
	if (engine->gui.color_and_material.color_being_changed
		== CAP_CHECKERBOARD_COLOR)
	{
		engine->gui.color_and_material.color_being_changed = BASE_COLOR;
		draw_toggle_box(engine->gui.color_and_material.\
			cap_checkered_pattern_color_toggle_box, false);
	}
}
