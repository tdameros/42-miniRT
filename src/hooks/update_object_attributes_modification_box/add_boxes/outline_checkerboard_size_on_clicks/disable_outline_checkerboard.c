/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disable_outline_checkerboard.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 09:07:03 by vfries            #+#    #+#             */
/*   Updated: 2023/09/24 09:25:08 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "object.h"
#include "hooks.h"

void	disable_outline_checkerboard(t_engine *engine, t_object *object)
{
	object->material.textures.outline.texture_type = NONE;
	if (engine->gui.color_and_material.color_being_changed
		== OUTLINE_CHECKERBOARD_COLOR)
	{
		engine->gui.color_and_material.color_being_changed = BASE_COLOR;
		draw_toggle_box(engine->gui.color_and_material.\
			outline_checkered_pattern_color_toggle_box, false);
	}
}
