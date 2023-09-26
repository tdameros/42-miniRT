/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 00:40:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/24 00:40:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"

void	set_outline_checkerboard(t_material *material,
			const t_vector2f size,
			const t_vector3f albedo)
{
	material->textures.outline.texture_type = CHECKERBOARD;
	material->textures.outline.checkerboard.size.x = size.x;
	material->textures.outline.checkerboard.size.y = size.y;
	material->textures.outline.checkerboard.albedo = albedo;
}

void	set_cap_checkerboard(t_material *material,
			const t_vector2f size,
			const t_vector3f albedo)
{
	material->textures.cap.texture_type = CHECKERBOARD;
	material->textures.cap.checkerboard.size.x = size.x;
	material->textures.cap.checkerboard.size.y = size.y;
	material->textures.cap.checkerboard.albedo = albedo;
}
