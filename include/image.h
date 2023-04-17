/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 10:45:43 by vfries            #+#    #+#             */
/*   Updated: 2023/04/15 10:45:44 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include "struct/t_window.h"

typedef struct s_image
{
	void	*image;
	char	*address;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}	t_image;

void	init_image(t_image *image, t_window *window, int height, int width);
int		init_image_from_xpm(t_image *image, t_window *window, char *xmp_file);
void	put_pixel_on_img(t_image *image, int y, int x, unsigned int color);
void	change_image_color(t_image *image, unsigned int color);
void	round_image_corners(t_image *image, int radius);

#endif //IMAGE_H
