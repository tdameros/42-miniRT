/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 21:50:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/06/16 21:50:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "material.h"
#include "object.h"
#include "libft.h"

static int	surface_deep_copy(t_surface *dst, const t_surface *src);
static int	ppm_p6_deep_copy(t_ppm_p6 *dst, const t_ppm_p6 *src);

t_material	material_create(const t_vector3f albedo,
							const float reflect_intensity,
							const float specular_intensity)
{
	t_material	material;

	material.textures = create_empty_texture();
	material.albedo = albedo;
	material.reflection = reflect_intensity;
	material.specular = specular_intensity;
	return (material);
}

void	material_free(t_material *material)
{
	free_outline_texture(material);
	free_cap_texture(material);
	free_outline_normals_map(material);
	free_cap_normals_map(material);
}

int	material_deep_copy(t_material *dst, const t_material *src)
{
	if (dst == src)
		return (0);
	material_free(dst);
	dst->albedo = src->albedo;
	dst->reflection = src->reflection;
	dst->specular = src->specular;
	if (surface_deep_copy(&dst->textures.outline,
			&src->textures.outline) < 0)
	{
		material_free(dst);
		return (-1);
	}
	if (surface_deep_copy(&dst->textures.cap,
			&src->textures.cap) < 0)
	{
		material_free(dst);
		return (-1);
	}
	return (0);
}

// Don't free if malloc fail
static int	surface_deep_copy(t_surface *dst, const t_surface *src)
{
	dst->texture_type = src->texture_type;
	dst->checkerboard = src->checkerboard;
	dst->has_normals_map = src->has_normals_map;
	if (ppm_p6_deep_copy(&dst->texture, &src->texture) < 0)
		return (-1);
	if (ppm_p6_deep_copy(&dst->normals_map, &src->normals_map) < 0)
		return (-1);
	if (src->texture_file == NULL)
		dst->texture_file = NULL;
	else
	{
		dst->texture_file = ft_strdup(src->texture_file);
		if (dst->texture_file == NULL)
			return (-1);
	}
	if (src->normals_map_file == NULL)
		dst->normals_map_file = NULL;
	else
	{
		dst->normals_map_file = ft_strdup(src->normals_map_file);
		if (dst->normals_map_file == NULL)
			return (-1);
	}
	return (0);
}

static int	ppm_p6_deep_copy(t_ppm_p6 *dst, const t_ppm_p6 *src)
{
	const size_t	size_in_bytes = sizeof(*src->pixels) * src->size;

	dst->width = src->width;
	dst->height = src->height;
	dst->size = src->size;
	if (src->pixels == NULL)
		dst->pixels = NULL;
	else
	{
		dst->pixels = malloc(size_in_bytes);
		if (dst->pixels == NULL)
			return (-1);
		ft_memcpy(dst->pixels, src->pixels, size_in_bytes);
	}
	return (0);
}
