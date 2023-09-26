/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 06:18:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/18 03:31:27 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>

#include "material.h"

static bool	is_default_material(t_material material);
static int	write_outline_texture(t_material material, int fd);
static int	write_cap_texture(t_material material, int fd);

int	write_material(t_material material, int fd)
{
	ssize_t	return_code;

	return_code = 1;
	if (is_default_material(material))
		return (0);
	if (dprintf(fd, "ma") < 0)
		return (-1);
	if (material.reflection != 0.f)
		return_code = dprintf(fd, "\treflection:%f", material.reflection);
	if (return_code < 0)
		return (-1);
	if (material.specular != 0.f)
		return_code = dprintf(fd, "\tspecular:%f", material.specular);
	if (return_code < 0)
		return (-1);
	if (write_outline_texture(material, fd) < 0)
		return (-1);
	if (write_cap_texture(material, fd) < 0)
		return (-1);
	if (dprintf(fd, "\n") < 0)
		return (-1);
	return (0);
}

static	bool	is_default_material(t_material material)
{
	if (material.reflection != 0.f)
		return (false);
	else if (material.specular != 0.f)
		return (false);
	else if (material.textures.outline.texture_type != NONE)
		return (false);
	else if (material.textures.outline.has_normals_map)
		return (false);
	else if (material.textures.cap.texture_type != NONE)
		return (false);
	else if (material.textures.cap.has_normals_map)
		return (false);
	return (true);
}

static int	write_outline_texture(t_material material, int fd)
{
	ssize_t	return_code;

	return_code = 1;
	if (material.textures.outline.texture_type == PPM_TEXTURE)
		return_code = dprintf(fd, "\toutline_texture:\"%s\"",
				material.textures.outline.texture_file);
	if (return_code < 0)
		return (-1);
	if (material.textures.outline.texture_type == CHECKERBOARD)
		return_code = dprintf(fd, "\toutline_checkerboard:%u,%u-%f,%f,%f",
				(uint32_t)material.textures.outline.checkerboard.size.x,
				(uint32_t)material.textures.outline.checkerboard.size.y,
				material.textures.outline.checkerboard.albedo.x * 255.f,
				material.textures.outline.checkerboard.albedo.y * 255.f,
				material.textures.outline.checkerboard.albedo.z * 255.f);
	if (return_code < 0)
		return (-1);
	if (material.textures.outline.has_normals_map)
		return_code = dprintf(fd, "\toutline_normal_map:\"%s\"",
				material.textures.outline.normals_map_file);
	if (return_code < 0)
		return (-1);
	return (0);
}

static int	write_cap_texture(t_material material, int fd)
{
	ssize_t	return_code;

	return_code = 1;
	if (material.textures.cap.texture_type == PPM_TEXTURE)
		return_code = dprintf(fd, "\tcap_texture:\"%s\"",
				material.textures.cap.texture_file);
	if (return_code < 0)
		return (-1);
	if (material.textures.cap.texture_type == CHECKERBOARD)
		return_code = dprintf(fd, "\tcap_checkerboard:%f,%f-%f,%f,%f",
				material.textures.cap.checkerboard.size.x,
				material.textures.cap.checkerboard.size.y,
				material.textures.cap.checkerboard.albedo.x * 255.f,
				material.textures.cap.checkerboard.albedo.y * 255.f,
				material.textures.cap.checkerboard.albedo.z * 255.f);
	if (return_code < 0)
		return (-1);
	if (material.textures.cap.has_normals_map)
		return_code = dprintf(fd, "\tcap_normal_map:\"%s\"",
				material.textures.cap.normals_map_file);
	if (return_code < 0)
		return (-1);
	return (0);
}
