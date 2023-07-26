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
	material->texture.outline_type = CHECKERBOARD;
	material->texture.outline_checkerboard.size.x = size.x;
	material->texture.outline_checkerboard.size.y = size.y;
	material->texture.outline_checkerboard.albedo = albedo;
}

void	set_cap_checkerboard(t_material *material,
							const t_vector2f size,
							const t_vector3f albedo)
{
	material->texture.cap_type = CHECKERBOARD;
	material->texture.cap_checkerboard.size.x = size.x;
	material->texture.cap_checkerboard.size.y = size.y;
	material->texture.cap_checkerboard.albedo = albedo;
}
