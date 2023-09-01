/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 07:33:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/31 07:33:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

#include "libft.h"

#include "material.h"

int	set_outline_normals_map(t_material *material, const char *filename)
{
	t_ppm_p6	ppm;

	free_outline_normals_map(material);
	if (initialize_ppm_p6_file(&ppm, filename) < 0)
		return (-1);
	material->texture.outline.normals_map_file = ft_strdup(filename);
	if (material->texture.outline.normals_map_file == NULL)
	{
		free_outline_normals_map(material);
		return (-1);
	}
	material->texture.outline.normals_map = ppm;
	material->texture.outline.has_normals_map = true;
	return (0);
}

int	set_cap_normals_map(t_material *material, const char *filename)
{
	t_ppm_p6	ppm;

	free_cap_normals_map(material);
	if (initialize_ppm_p6_file(&ppm, filename) < 0)
		return (-1);
	material->texture.cap.normals_map_file = ft_strdup(filename);
	if (material->texture.cap.normals_map_file == NULL)
	{
		free_cap_normals_map(material);
		return (-1);
	}
	material->texture.cap.normals_map = ppm;
	material->texture.cap.has_normals_map = true;
	return (0);
}

void	free_outline_normals_map(t_material *material)
{
	free(material->texture.outline.normals_map.pixels);
	free(material->texture.outline.normals_map_file);
	ft_bzero(&material->texture.outline.normals_map,
		sizeof(material->texture.outline.normals_map));
	material->texture.outline.normals_map_file = NULL;
	material->texture.outline.has_normals_map = false;
}

void	free_cap_normals_map(t_material *material)
{
	free(material->texture.cap.normals_map.pixels);
	free(material->texture.cap.normals_map_file);
	ft_bzero(&material->texture.cap.normals_map,
		sizeof(material->texture.cap.normals_map));
	material->texture.cap.normals_map_file = NULL;
	material->texture.cap.has_normals_map = false;
}
