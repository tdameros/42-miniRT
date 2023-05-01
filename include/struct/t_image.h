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

#ifndef T_IMAGE_H
# define T_IMAGE_H

# include "struct/t_window.h"

typedef struct s_image
{
	void	*data;
	char	*address;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}	t_image;

int				init_image(t_image *image, t_window *window, int width,
					int height);
int				init_image_from_xpm(t_image *image, t_window *window,
					char *xmp_file);
void			destroy_t_image(t_window *minirt_window, t_image *image);
void			put_pixel_on_image(t_image *image, int y, int x,
					unsigned int color);
unsigned int	get_image_pixel_color(t_image *image, int y, int x);
void			change_image_color(t_image *image, unsigned int color);
void			round_image_corners(t_image *image, int radius);

#endif //T_IMAGE_H
