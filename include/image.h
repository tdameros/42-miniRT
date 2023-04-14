#ifndef IMAGE_H
# define IMAGE_H

# include "struct/window.h"

typedef struct s_image
{
	void	*image;
	char	*address;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

void	init_image(t_image *image, t_window *window, int height, int width);

#endif //IMAGE_H
