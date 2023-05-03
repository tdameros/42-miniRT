#include <math.h>
#include "struct/t_image.h"
#include "struct/t_point_int_2d.h"
#include "struct/t_color.h"

static unsigned int	mix_colors(unsigned int added_color, unsigned int base_color);

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
//						unsigned int base_color_int)
//{
//	t_color			added_color;
//	t_color			base_color;
//	unsigned int	added_color_transparency;
//	float			transparency;
//	float			inverse_transparency;
//
//	added_color_transparency = added_color_int >> 24;
//	if (added_color_transparency == 255)
//		return (base_color_int);
//	if (added_color_transparency == 0)
//		return (added_color_int);
//	added_color = get_t_color_from_uint(added_color_int);
//	base_color = get_t_color_from_uint(base_color_int);
//	inverse_transparency = (float)added_color_transparency / 255.f;
//	transparency = 1.f - inverse_transparency;
//	return (rgb_to_uint((t_color){
//			.r = round(transparency * (float)added_color.r
//				+ inverse_transparency * (float)base_color.r),
//			.g = round(transparency * (float)added_color.g
//				+ inverse_transparency * (float)base_color.g),
//			.b = round(transparency * (float)added_color.b
//				+ inverse_transparency * (float)base_color.b) \
//		}));
//}

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
		((unsigned int)roundf(
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
