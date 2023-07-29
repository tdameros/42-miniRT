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

t_texture	create_empty_texture(void)
{
	t_texture	texture;

	ft_bzero(&texture, sizeof(texture));
	texture.outline.texture_type = NONE;
	texture.cap.texture_type = NONE;
	texture.outline.checkerboard.size = (t_vector2f){1, 1};
	texture.cap.checkerboard.size = (t_vector2f){1, 1};
	return (texture);
}

int	set_outline_ppm_texture(t_material *material, const char *filename)
{
	t_ppm_p6	ppm;

	if (initialize_ppm_p6_file(&ppm, filename) < 0)
		return (-1);
	material->texture.outline.texture = ppm;
	material->texture.outline.texture_type = PPM_TEXTURE;
	return (0);
}

int	set_outline_ppm_normal(t_material *material, const char *filename)
{
	t_ppm_p6	ppm;

	if (initialize_ppm_p6_file(&ppm, filename) < 0)
		return (-1);
	material->texture.outline.bump_map = ppm;
	material->texture.outline.has_bum_map = true;
	return (0);
}

int	set_cap_ppm_texture(t_material * material, const char *filename)
{
	t_ppm_p6	ppm;

	if (initialize_ppm_p6_file(&ppm, filename) < 0)
		return (-1);
	material->texture.cap.texture = ppm;
	material->texture.cap.texture_type = PPM_TEXTURE;
	return (0);
}


void	free_outline_texture(t_material *material)
{
	free(material->texture.outline.texture.pixels);
	material->texture.outline.texture_type = CHECKERBOARD;
	ft_bzero(&material->texture.outline.checkerboard,
		sizeof(material->texture.outline.checkerboard));
}

void	free_cap_texture(t_material *material)
{
	free(material->texture.cap.texture.pixels);
	material->texture.cap.texture_type = CHECKERBOARD;
	ft_bzero(&material->texture.cap.checkerboard,
		sizeof(material->texture.cap.checkerboard));
}
