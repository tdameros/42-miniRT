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
