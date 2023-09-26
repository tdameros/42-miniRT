/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_image_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 01:47:32 by vfries            #+#    #+#             */
/*   Updated: 2023/09/24 03:40:26 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void	change_image_color(t_image *image, unsigned int color)
{
	const unsigned int	*image_end = image->address + image->height
		* image->width;
	unsigned int		*cursor;

	cursor = image->address;
	while (cursor < image_end)
		*cursor++ = color;
}

void	add_color_to_image(t_image *image, unsigned int color)
{
	const unsigned int	*image_end = image->address + image->height
		* image->width;
	unsigned int		*cursor;

	cursor = image->address;
	while (cursor < image_end)
	{
		*cursor = mix_colors(color, *cursor);
		cursor++;
	}
}
