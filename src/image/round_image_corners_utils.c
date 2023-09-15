#include <stdbool.h>
#include <math.h>

#include "image.h"

bool	is_in_top_left_corner(int x, int y, int radius)
{
	return (y < radius && x < radius
		&& powf(y - radius, 2) + powf(x - radius, 2) > powf(radius, 2));
}

bool	is_in_top_right_corner(int x, int y, int radius, t_image *image)
{
	return (y < radius && x >= image->width - radius
		&& powf(y - radius, 2) + powf(x - image->width + radius, 2)
		> powf(radius, 2));
}

bool	is_in_bottom_left_corner(int x, int y, int radius, t_image *image)
{
	return (y >= image->height - radius && x < radius
		&& powf(y - image->height + radius, 2)
		+ powf(x - radius, 2) > powf(radius, 2));
}

bool	is_in_bottom_right_corner(int x, int y, int radius, t_image *image)
{
	return (y >= image->height - radius && x >= image->width - radius
		&& powf(y - image->height + radius, 2)
		+ powf(x - image->width + radius, 2) > powf(radius, 2));
}
