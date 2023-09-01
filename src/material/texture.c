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
	return (texture);
}

int	set_outline_texture(t_material *material, const char *filename)
{
	t_ppm_p6	ppm;

	free_outline_texture(material);
	if (initialize_ppm_p6_file(&ppm, filename) < 0)
		return (-1);
	material->texture.outline.texture_file = ft_strdup(filename);
	if (material->texture.outline.texture_file == NULL)
	{
		free_outline_texture(material);
		return (-1);
	}
	material->texture.outline.texture = ppm;
	material->texture.outline.texture_type = PPM_TEXTURE;
	return (0);
}

int	set_cap_texture(t_material *material, const char *filename)
{
	t_ppm_p6	ppm;

	free_cap_texture(material);
	if (initialize_ppm_p6_file(&ppm, filename) < 0)
		return (-1);
	material->texture.cap.texture_file = ft_strdup(filename);
	if (material->texture.cap.texture_file == NULL)
	{
		free_cap_texture(material);
		return (-1);
	}
	material->texture.cap.texture = ppm;
	material->texture.cap.texture_type = PPM_TEXTURE;
	return (0);
}

void	free_outline_texture(t_material *material)
{
	free(material->texture.outline.texture.pixels);
	free(material->texture.outline.texture_file);
	material->texture.outline.texture_file = NULL;
	material->texture.outline.texture_type = NONE;
	ft_bzero(&material->texture.outline.checkerboard,
		sizeof(material->texture.outline.checkerboard));
	ft_bzero(&material->texture.outline.texture,
		sizeof(material->texture.outline.texture));
}

void	free_cap_texture(t_material *material)
{
	free(material->texture.cap.texture.pixels);
	free(material->texture.cap.texture_file);
	material->texture.cap.texture_file = NULL;
	material->texture.cap.texture_type = NONE;
	ft_bzero(&material->texture.cap.checkerboard,
		sizeof(material->texture.cap.checkerboard));
	ft_bzero(&material->texture.cap.texture,
		sizeof(material->texture.cap.texture));
}
