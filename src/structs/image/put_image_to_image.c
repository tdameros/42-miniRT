#include <stddef.h>
#include "struct/t_image.h"
#include "struct/t_point_int_2d.h"

static unsigned int	mix_colors(unsigned int added_color,
						unsigned int base_color);

inline void	put_image_to_image(register t_image *destination,
				const t_image *source, t_point_int_2d position)
{
	int				position_x_backup;
	register int	y;
	register int	x;
	int				tmp;

	position_x_backup = position.x;
	y = (position.y < 0) * -position.y;
	position.y = (position.y > 0) * position.y;
	while (position.y < destination->height && y < source->height)
	{
		x = (position.x < 0) * -position.x;
		position.x = (position.x > 0) * position.x;
		tmp = position.y * destination->line_length + position.x;
		while (position.x < destination->width && x < source->width)
		{
			destination->address[tmp]
				= mix_colors(source->address[y * source->line_length + x++],
					destination->address[tmp]);
			position.x++;
			tmp++;
		}
		position.x = position_x_backup;
		position.y++;
		y++;
	}
}

inline void	put_background(t_image *destination, const t_image *source)
{
	register const unsigned int	*dest_end
		= destination->address + destination->height * destination->line_length;
	register unsigned int		*dest_curr;
	register unsigned int		*source_curr;

	source_curr = source->address;
	dest_curr = destination->address;
	while (dest_curr < dest_end)
		*dest_curr++ = *source_curr++;
}

inline void	put_image_to_image_unsafe(register t_image *destination,
				const t_image *source, t_point_int_2d position)
{
	register const unsigned int	*source_end
		= source->address + source->height * source->line_length;
	register unsigned int		*source_curr;
	register unsigned int		*dest_curr;
	register int				x;


	dest_curr = destination->address + position.y * destination->line_length;
	x = 0;
	source_curr = source->address;
	while (source_curr < source_end)
	{
		dest_curr[position.x + x]
			= mix_colors(*source_curr++, dest_curr[position.x + x]);
		x++;
		if (x >= source->width)
		{
			x = 0;
			dest_curr += destination->line_length;
		}
	}
}

static unsigned int	mix_colors(unsigned int added_color,
						unsigned int base_color)
{
	const unsigned int	added_color_transparency = added_color >> 24;
//	float				inverse_transparency;
//	float				transparency;

	if (added_color_transparency == 255)
		return (base_color);
	if (added_color_transparency == 0)
		return (added_color);

	// TODO check how it looks with this (Applies 0.25 transparency instead of calculating actual transparency)
	//  								 (is faster but doesn't allow precise transparency)
	return (((((added_color & 0x00FF0000) >> 16) / 4 * 3 + ((base_color & 0x00FF0000) / 4 >> 16))) << 16
		| ((((added_color & 0x0000FF00) >> 8) / 4 * 3 + ((base_color & 0x0000FF00) >> 8) / 4)) << 8
		| (((added_color & 0x000000FF) / 4 * 3 + (base_color & 0x000000FF) / 4)));


//	inverse_transparency = added_color_transparency / 255.f;
//	transparency = 1.f - inverse_transparency;
//	return (((unsigned int)(transparency * ((added_color & 0x00FF0000) >> 16)
//			+ inverse_transparency * ((base_color & 0x00FF0000) >> 16)))
//				<< 16
//		| ((unsigned int)(transparency * ((added_color & 0x0000FF00) >> 8)
//			+ inverse_transparency * ((base_color & 0x0000FF00) >> 8)))
//				<< 8
//		| (unsigned int)(transparency * (added_color & 0x000000FF)
//			+ inverse_transparency * (base_color & 0x000000FF)));
}
