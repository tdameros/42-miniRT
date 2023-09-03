/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:56:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/13 14:56:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <errno.h>

static int	parse_header(t_ppm_p6 *ppm, t_string *file_content);
static char	*get_line(t_string *file_content, int line_number);
static int	parse_size(t_ppm_p6 *ppm, char *size_line);
static int	convert_binary_pixels_to_vector(t_ppm_p6 *ppm,
				const unsigned char *pixels);

int	initialize_ppm_p6_file(t_ppm_p6 *ppm, const char *filename)
{
	t_string	file_content;

	file_content = ft_read_file(filename);
	if (file_content.data == NULL)
		return (-1);
	if (parse_header(ppm, &file_content) < 0)
		return (-1);
	ppm->pixels = malloc(sizeof(*ppm->pixels) * ppm->size);
	if (ppm->pixels == NULL)
		return (-1);
	convert_binary_pixels_to_vector(ppm,
		(unsigned char *) get_line(&file_content, 4));
	return (0);
}

static int	parse_header(t_ppm_p6 *ppm, t_string *file_content)
{
	const char	*type_line = get_line(file_content, 1);
	const char	*size_line = get_line(file_content, 2);
	const char	*color_size = get_line(file_content, 3);
	const char	*pixels = get_line(file_content, 4);

	if (type_line == NULL || size_line == NULL
		|| color_size == NULL || pixels == NULL)
		return (-1);
	if (ft_strncmp(type_line, "P6\n", 3) != 0
		|| ft_strncmp(color_size, "255\n", 4) != 0)
		return (-1);
	*((char *) color_size - 1) = '\0';
	if (parse_size(ppm, (char *) size_line) < 0)
		return (-1);
	*((char *) color_size - 1) = '\n';
	*((char *) pixels - 1) = '\0';
	ppm->size = ppm->width * ppm->height;
	if (file_content->len - (ft_strlen(file_content->data) + 1)
		!= ppm->size * 3)
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

static int	parse_size(t_ppm_p6 *ppm, char *size_line)
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
	ppm->width = ft_atoi(split_line[0]);
	ppm->height = ft_atoi(split_line[1]);
	ft_free_split(split_line);
	if (errno == ERANGE)
		return (-1);
	return (0);
}

static int	convert_binary_pixels_to_vector(t_ppm_p6 *ppm,
											const unsigned char *pixels)
{
	unsigned int		texture_pixels_index;
	unsigned int		i;

	texture_pixels_index = 0;
	i = 0;
	while (texture_pixels_index < ppm->size)
	{
		ppm->pixels[texture_pixels_index] = (t_vector3f){
			((float) pixels[i] / 255),
			((float) pixels[i + 1] / 255),
			((float)pixels[i + 2] / 255)};
		texture_pixels_index++;
		i += 3;
	}
	return (0);
}
