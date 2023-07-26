/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_draw_outline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:53:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/14 11:53:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void	image_draw_outline(t_image *image, const int width,
			const unsigned int color)
{
	image_draw_top_outline(image, width, color);
	image_draw_bottom_outline(image, width, color);
	image_draw_left_outline(image, width, color);
	image_draw_right_outline(image, width, color);
}

void	image_draw_top_outline(t_image *image, const int width,
			const unsigned int color)
{
	int				x;
	int				i;

	x = -1;
	while (++x < image->width)
	{
		i = 0;
		while (i < width && x + i < image->width)
		{
			image->address[x + i] = color;
			i++;
		}
	}
}

void	image_draw_bottom_outline(t_image *image, const int width,
			const unsigned int color)
{
	int				x;
	const size_t	last_line_index = (image->height - 1) * image->width;
	int				i;

	x = -1;
	while (++x < image->width)
	{
		i = 0;
		while (i < width && (size_t)image->width * i < last_line_index)
		{
			image->address[last_line_index - (image->width * i) + x] = color;
			i++;
		}
	}
}

void	image_draw_left_outline(t_image *image, const int width,
			const unsigned int color)
{
	size_t			line;
	int				i;

	line = 0;
	while (line < image->size)
	{
		i = 0;
		while (i < width && i < image->width)
		{
			image->address[line + i] = color;
			i++;
		}
		line += image->width;
	}
}

void	image_draw_right_outline(t_image *image, const int width,
			const unsigned int color)
{
	size_t			line;
	const int		last_x = image->width - 1;
	int				i;

	line = 0;
	while (line < image->size)
	{
		i = 0;
		while (i < width && i <= last_x)
		{
			image->address[line + last_x - i] = color;
			i++;
		}
		line += image->width;
	}
}
