/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:56:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/12 14:56:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>

#include "libft.h"

#include "object.h"

static int	parse_header(t_object *object, t_string *file_content);
static int	parse_size(t_texture *texture, char *size_line);
static char *get_line(t_string *file_content, int line_number);
static int	convert_binary_pixels_to_vector(t_texture *texture,
											  const unsigned char *pixels);

int	load_texture_object(t_object *object, char *file)
{
	t_string	file_content;
	t_texture	*texture;

	texture = &object->material.texture;
	file_content = ft_read_file(file);
	if (parse_header(object, &file_content) < 0)
		return (-1);
	texture->pixels = malloc(sizeof(*texture->pixels) * texture->size);
	if (texture->pixels == NULL)
		return (-1);
	convert_binary_pixels_to_vector(texture,
		(unsigned char *) get_line(&file_content, 4));
	return (0);
}

static int	parse_header(t_object *object, t_string *file_content)
{
	const char	*type_line = get_line(file_content, 1);
	const char	*size_line = get_line(file_content, 2);
	const char	*color_size = get_line(file_content, 3);
	const char	*pixels = get_line(file_content, 4);
	t_texture	*texture = &object->material.texture;

	if (type_line == NULL || size_line == NULL || color_size == NULL || pixels == NULL)
		return (-1);
	if (ft_strncmp(type_line, "P6\n", 3) != 0
		|| ft_strncmp(color_size, "255\n", 4) != 0)
		return (-1);
	*((char *) color_size - 1) = '\0';
	if (parse_size(texture, (char *) size_line) < 0)
		return (-1);
	*((char *) color_size - 1) = '\n';
	*((char *) pixels - 1) = '\0';
	texture->size = texture->width * texture->height;
	if (file_content->len - (ft_strlen(file_content->data) + 1) != texture->size * 3)
	{
		*((char *) pixels - 1) = '\n';
		return (-1);
	}
	*((char *) pixels - 1) = '\n';
	return (0);
}

static char	*get_line(t_string *file_content, int line_number)
{
	int		i;
	char	*line;
	char	*new_line;

	i = 1;
	line = file_content->data;
	while (i < line_number)
	{
		new_line = ft_strchr(line, '\n');
		if (new_line == NULL || new_line == line)
			return (NULL);
		line = new_line + 1;
		i++;
	}
	return (line);
}

static int	parse_size(t_texture *texture, char *size_line)
{
	char	**split_line;

	if (size_line == NULL)
		return (-1);
	split_line = ft_split(size_line, ' ');
	if (split_line == NULL)
		return (-1);
	if (ft_split_len(split_line) != 2)
	{
		ft_free_split(split_line);
		return (-1);
	}
	texture->width = ft_atoi(split_line[0]);
	texture->height = ft_atoi(split_line[1]);
	ft_free_split(split_line);
	if (errno == ERANGE)
		return (-1);
	return (0);
}

static int	convert_binary_pixels_to_vector(t_texture *texture,
											const unsigned char *pixels)
{
	unsigned int		texture_pixels_index;
	unsigned int		i;

	texture_pixels_index = 0;
	i = 0;
	while (texture_pixels_index < texture->size)
	{
		texture->pixels[texture_pixels_index] = (t_vector3f){
			((float) pixels[i] / 255),
			((float) pixels[i + 1] / 255),
			((float)pixels[i + 2] / 255)};
		texture_pixels_index++;
		if (texture_pixels_index == 111184)
		{
			ft_printf("%d x %d\n", texture->width, texture->height);
			ft_printf("%d %d %d\n", pixels[i], pixels[i + 1], pixels[i + 2]);
		}
		i += 3;
	}
	return (0);
}
