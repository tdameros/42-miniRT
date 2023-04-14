#ifndef IMAGE_H
# define IMAGE_H

typedef struct s_image
{
	void	*image;
	char	*address;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

#endif //IMAGE_H
