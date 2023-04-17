#include <stddef.h>

#include "mlx.h"

#include "image.h"
#include "struct/t_window.h"
#include "libft.h"

void	init_image(t_image *image, t_window *window, int height, int width)
{
	image->image = mlx_new_image(window->mlx, width, height); // TODO can this fail?
	image->address = mlx_get_data_addr(image->image, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	image->height = height;
	image->width = width;
}

int	init_image_from_xpm(t_image *image, t_window *window, char *xmp_file)
{
	image->image = mlx_xpm_file_to_image(window->mlx, xmp_file,
			&image->width, &image->height);
	if (image->image == NULL)
	{
		ft_putstr_fd("Error: mlx_xpm_file_to_image failed\n", STDERR_FILENO);
		return (1);
	}
	image->address = mlx_get_data_addr(image->image, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	return (0);
}

void	put_pixel_on_image(t_image *image, int y, int x, unsigned int color)
{
	char	*destination;

	destination = image->address
		  + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int *)destination = color;
}

unsigned int	get_image_pixel_color(t_image *image, int y, int x)
{
	const char	*pixel = image->address
			+ (y * image->line_length + x * (image->bits_per_pixel / 8));

	return (*(const unsigned int *)pixel);
}

void	change_image_color(t_image *image, unsigned int color)
{
	int	i;
	int	j;

	i = image->height;
	while (i--)
	{
		j = image->width;
		while (j--)
			put_pixel_on_image(image, i, j, color);
	}
}
