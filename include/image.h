/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_image.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 10:45:43 by vfries            #+#    #+#             */
/*   Updated: 2023/05/06 20:05:19 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include "window.h"
# include "math/vector.h"

typedef struct s_image
{
	void			*data;
	unsigned int	*address;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				height;
	int				width;
}	t_image;

int				init_image(t_image *image, t_window *window, int width,
					int height);
int				init_image_from_xpm(t_image *image, t_window *window,
					char *xmp_file);
void			destroy_t_image(t_window *minirt_window, t_image *image);
void			put_pixel_on_image(t_image *image, int y, int x,
					unsigned int color);
unsigned int	get_image_pixel_color(const t_image *image, int y, int x);
void			change_image_color(t_image *image, unsigned int color);
void			round_image_corners(t_image *image, int radius);
void			put_image_to_image(t_image *destination, const t_image *source,
								   t_vector2i position);
void			put_image_to_image_unsafe(register t_image *destination,
										  const t_image *source, t_vector2i position);
void			put_background(t_image *destination, const t_image *source);

void			draw_circle(t_image *image, t_vector2i circle_center,
					float radius, unsigned int color);
void			draw_circle_with_shadow(t_image *image,
					t_vector2i circle_center, float radius, t_vector3f color);

#endif //IMAGE_H
