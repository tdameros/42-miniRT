/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:39:02 by vfries            #+#    #+#             */
/*   Updated: 2023/07/30 18:39:02 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "mlx.h"
#include "libft.h"

#include "image.h"
#include "window.h"

void	init_image(t_image *image, t_window *window, int width, int height)
{
	image->data = mlx_new_image(window->mlx, width, height);
	if (image->data == NULL)
		ft_fatal_error("Error: mlx_new_image failed\n");
	image->address = (unsigned int *)mlx_get_data_addr(image->data,
			&image->bits_per_pixel, &image->line_length, &image->endian);
	image->line_length /= 4;
	image->height = height;
	image->width = width;
	image->size = height * width;
	image->limit = image->address + image->size;
}

void	init_image_from_xpm(t_image *image, t_window *window, char *xmp_file)
{
	image->data = mlx_xpm_file_to_image(window->mlx, xmp_file,
			&image->width, &image->height);
	if (image->data == NULL)
		ft_fatal_error("Error: mlx_xpm_file_to_image failed\n");
	image->address = (unsigned int *)mlx_get_data_addr(image->data,
			&image->bits_per_pixel, &image->line_length, &image->endian);
	image->line_length /= 4;
	image->size = image->height * image->width;
	image->limit = image->address + image->size;
}

inline void	put_pixel_on_image(t_image *image, int y, int x,
					unsigned int color)
{
	image->address[y * image->line_length + x] = color;
}

inline unsigned int	get_image_pixel_color(const t_image *image, const int y,
			const int x)
{
	return (image->address[y * image->line_length + x]);
}
