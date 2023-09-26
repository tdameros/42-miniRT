/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:31:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/13 17:31:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"
#include "parsing.h"

t_textures	create_empty_texture(void)
{
	t_textures	texture;

	ft_bzero(&texture, sizeof(texture));
	texture.outline.texture_type = NONE;
	texture.cap.texture_type = NONE;
	return (texture);
}

int	set_outline_texture(t_material *material, const char *filename)
{
	t_ppm_p6	ppm;

	free_outline_texture(material);
	if (initialize_ppm_p6_file(&ppm, filename) < 0)
		return (-1);
	material->textures.outline.texture_file = ft_strdup(filename);
	if (material->textures.outline.texture_file == NULL)
	{
		free_outline_texture(material);
		return (-1);
	}
	material->textures.outline.texture = ppm;
	material->textures.outline.texture_type = PPM_TEXTURE;
	return (0);
}

int	set_cap_texture(t_material *material, const char *filename)
{
	t_ppm_p6	ppm;

	free_cap_texture(material);
	if (initialize_ppm_p6_file(&ppm, filename) < 0)
		return (-1);
	material->textures.cap.texture_file = ft_strdup(filename);
	if (material->textures.cap.texture_file == NULL)
	{
		free_cap_texture(material);
		return (-1);
	}
	material->textures.cap.texture = ppm;
	material->textures.cap.texture_type = PPM_TEXTURE;
	return (0);
}

void	free_outline_texture(t_material *material)
{
	free(material->textures.outline.texture.pixels);
	free(material->textures.outline.texture_file);
	material->textures.outline.texture_file = NULL;
	material->textures.outline.texture_type = NONE;
	ft_bzero(&material->textures.outline.checkerboard,
		sizeof(material->textures.outline.checkerboard));
	ft_bzero(&material->textures.outline.texture,
		sizeof(material->textures.outline.texture));
}

void	free_cap_texture(t_material *material)
{
	free(material->textures.cap.texture.pixels);
	free(material->textures.cap.texture_file);
	material->textures.cap.texture_file = NULL;
	material->textures.cap.texture_type = NONE;
	ft_bzero(&material->textures.cap.checkerboard,
		sizeof(material->textures.cap.checkerboard));
	ft_bzero(&material->textures.cap.texture,
		sizeof(material->textures.cap.texture));
}
