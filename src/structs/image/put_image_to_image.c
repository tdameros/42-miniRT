#include <math.h>

#include "struct/t_image.h"
#include "struct/t_point_int_2d.h"

static int			get_counter(int *position_counter);
static unsigned int	mix_colors(unsigned int added_color,
						unsigned int base_color);

inline void	put_image_to_image(t_image *destination, const t_image *source,
				t_point_int_2d position)
{
	int				position_x_backup;
	register int	y;
	register int	x;

	position_x_backup = position.x;
	y = get_counter(&position.y);
	while (position.y < destination->height && y < source->height)
	{
		x = get_counter(&position.x);
		while (position.x < destination->width && x < source->width)
		{
			put_pixel_on_image(destination, position.y, position.x,
				mix_colors(get_image_pixel_color(source, y, x++),
					get_image_pixel_color(destination, position.y, position.x))
				);
			position.x++;
		}
		position.x = position_x_backup;
		position.y++;
		y++;
	}
}

static inline int	get_counter(int *position_counter)
{
	int	counter;

	if (*position_counter >= 0)
		return (0);
	counter = -*position_counter;
	*position_counter = 0;
	return (counter);
}

static unsigned int	mix_colors(unsigned int added_color,
						unsigned int base_color)
{
	const unsigned int	added_color_transparency = added_color >> 24;
	float				transparency;
	float				inverse_transparency;

	if (added_color_transparency == 255)
		return (base_color);
	if (added_color_transparency == 0)
		return (added_color);
	inverse_transparency = (float)added_color_transparency / 255.f;
	transparency = 1.f - inverse_transparency;
	return (
		((unsigned int)roundf(\
			transparency * (float)((added_color & 0x00FF0000) >> 16)
			+ inverse_transparency * (float)((base_color & 0x00FF0000) >> 16)))
				<< 16
		| ((unsigned int)roundf(
			transparency * (float)((added_color & 0x0000FF00) >> 8)
			+ inverse_transparency * (float)((base_color & 0x0000FF00) >> 8)))
				<< 8
		| (unsigned int)roundf(transparency * (float)(added_color & 0x000000FF)
			+ inverse_transparency * (float)(base_color & 0x000000FF)));
}
