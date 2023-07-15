/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:31:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/13 17:31:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"
#include "parsing.h"

t_texture	texture_empty_create(void)
{
	t_texture	texture;

	texture.type = NONE;
	texture.has_bump_map = false;
	return (texture);
}

int	set_ppm_texture_in_material(t_material *material, const char *filename)
{
	t_ppm_p6	ppm;

	if (initialize_ppm_p6_file(&ppm, filename) < 0)
		return (-1);
	material->texture.texture_file = ppm;
	material->texture.type = PPM_TEXTURE;
	return (0);
}

void	set_checker_board_in_material(t_material *material,
									const t_vector2f size,
									const t_vector3f albedo)
{
	material->texture.type = CHECKER_BOARD;
	material->texture.checker_board.width = size.x;
	material->texture.checker_board.width = size.y;
	material->texture.checker_board.albedo = albedo;
}

void	free_texture_in_material(t_material *material)
{
	free(material->texture.texture_file.pixels);
	free(material->texture.bump_map.pixels);
	material->texture.type = NONE;
}