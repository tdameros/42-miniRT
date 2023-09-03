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
	material->texture.outline.texture_type = CHECKERBOARD;
	material->texture.outline.checkerboard.size.x = size.x;
	material->texture.outline.checkerboard.size.y = size.y;
	material->texture.outline.checkerboard.albedo = albedo;
}

void	set_cap_checkerboard(t_material *material,
			const t_vector2f size,
			const t_vector3f albedo)
{
	material->texture.cap.texture_type = CHECKERBOARD;
	material->texture.cap.checkerboard.size.x = size.x;
	material->texture.cap.checkerboard.size.y = size.y;
	material->texture.cap.checkerboard.albedo = albedo;
}
