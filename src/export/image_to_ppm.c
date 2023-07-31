/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_to_ppm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 08:07:01 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/31 08:07:02 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include "libft.h"

#include "engine.h"

static char				*get_ppm_header(const t_image *image);
static unsigned char	*get_ppm_pixels(const t_image *image);
static int				close_error(int fd);

int	export_image_to_ppm(const t_image *image, const char *output_file)
{
	const int		fd = open(output_file, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	char			*header;
	unsigned char	*pixels;
	ssize_t			return_code;

	if (fd < 0)
		return (-1);
	header = get_ppm_header(image);
	if (header == NULL)
		return (close_error(fd));
	return_code = write(fd, header, ft_strlen(header));
	free(header);
	if (return_code < 0)
		return (close_error(fd));
	pixels = get_ppm_pixels(image);
	if (pixels == NULL)
		return (close_error(fd));
	return_code = write(fd, pixels, image->size * 3);
	free(pixels);
	if (return_code < 0)
		return (close_error(fd));
	return (close(fd));
}

static char	*get_ppm_header(const t_image *image)
{
	char	*width;
	char	*height;
	char	*header[6];
	char	*result;

	width = ft_itoa(image->width);
	if (width == NULL)
		return (NULL);
	height = ft_itoa(image->height);
	if (height == NULL)
	{
		free(width);
		return (NULL);
	}
	header[0] = "P6\n";
	header[1] = width;
	header[2] = " ";
	header[3] = height;
	header[4] = "\n255\n";
	header[5] = NULL;
	result = ft_join_strs(header, "");
	free(width);
	free(height);
	return (result);
}

static unsigned char	*get_ppm_pixels(const t_image *image)
{
	unsigned char	*ppm_pixels;
	unsigned int	*transparent_pixels;
	unsigned int	i;

	ppm_pixels = malloc(image->size * 3 * sizeof(*ppm_pixels));
	if (ppm_pixels == NULL)
		return (NULL);
	transparent_pixels = image->address;
	i = 0;
	while (i < image->size)
	{
		ppm_pixels[i * 3] = (*transparent_pixels & 0x00FF0000) >> 16;
		ppm_pixels[i * 3 + 1] = (*transparent_pixels & 0x0000FF00) >> 8;
		ppm_pixels[i * 3 + 2] = (*transparent_pixels & 0x000000FF);
		transparent_pixels += 1;
		i++;
	}
	return (ppm_pixels);
}

static int	close_error(int fd)
{
	close(fd);
	return (-1);
}
