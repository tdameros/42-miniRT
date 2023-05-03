#include <math.h>
#include "struct/t_image.h"
#include "struct/t_point_int_2d.h"
#include "struct/t_color.h"

static unsigned int	mix_colors(unsigned int color_1, unsigned int color_2);

inline void	put_image_to_image(t_image *destination, const t_image *source,
				t_point_int_2d position)
{
	int				position_x_backup;
	register int	y;
	register int	x;

	position_x_backup = position.x;
	if (position.y < 0)
	{
		y = -position.y;
		position.y = 0;
	}
	else
		y = 0;
	while (position.y < destination->height && y < source->height)
	{
		if (position.x < 0)
		{
			x = -position.x;
			position.x = 0;
		}
		else
			x = 0;
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
//
//static unsigned int	mix_colors(unsigned int added_color_int,
//								unsigned int base_color_int)
//{
//	t_color		added_color;
//	t_color		base_color;
//	const float	transparency = 1.f - (float)(added_color_int >> 24) / 255.f;
//
//	if (transparency == 0.f)
//		return (base_color_int);
//	if (transparency == 1.f)
//		return (added_color_int);
//	added_color = get_t_color_from_uint(added_color_int);
//	base_color = get_t_color_from_uint(base_color_int);
//	return (rgb_to_uint((t_color){
//		.r = round(((float)added_color.r + (float)base_color.r * transparency) / 2.f),
//		.g = round(((float)added_color.g + (float)base_color.g * transparency) / 2.f),
//		.b = round(((float)added_color.b + (float)base_color.b * transparency) / 2.f)
//	}));
//}


static unsigned int	mix_colors(unsigned int added_color_int,
								  unsigned int base_color_int)
{
	t_color	added_color;
	t_color	base_color;
	int		added_color_transparency = added_color_int >> 24;
	float	transparency;

	if (added_color_transparency == 255)
		return (base_color_int);
	if (added_color_transparency == 0)
		return (added_color_int);
	transparency = 1.f - (float)added_color_transparency / 255.f;
	added_color = get_t_color_from_uint(added_color_int);
	base_color = get_t_color_from_uint(base_color_int);
	return (rgb_to_uint((t_color){
			.r = round(((float)added_color.r + (float)base_color.r * transparency) / 2.f),
			.g = round(((float)added_color.g + (float)base_color.g * transparency) / 2.f),
			.b = round(((float)added_color.b + (float)base_color.b * transparency) / 2.f)
	}));
}
