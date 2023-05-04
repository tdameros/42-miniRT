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
		while (position.x < destination->width && x < source->width)
		{
			tmp = position.y * destination->line_length + position.x;
			destination->address[tmp]
				= mix_colors(source->address[y * source->line_length + x++],
					destination->address[tmp]);
			position.x++;
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

static unsigned int	mix_colors(unsigned int added_color,
						unsigned int base_color)
{
	const unsigned int	added_color_transparency = added_color >> 24;
	float				inverse_transparency;
	float				transparency;

	if (added_color_transparency == 255)
		return (base_color);
	if (added_color_transparency == 0)
		return (added_color);

	// TODO check how it looks with this (Applies 0.5 transparency instead of calculating actual transparency)
	//  								 (is faster but doesn't allow precise transparency)
//	return (((((added_color & 0x00FF0000) >> 16) + ((base_color & 0x00FF0000) >> 16)) / 2) << 16
//		| ((((added_color & 0x0000FF00) >> 8) + ((base_color & 0x0000FF00) >> 8)) / 2) << 8
//		| (((added_color & 0x000000FF) + (base_color & 0x000000FF)) / 2));


	inverse_transparency = added_color_transparency / 255.f;
	transparency = 1.f - inverse_transparency;
	return (((unsigned int)(transparency * ((added_color & 0x00FF0000) >> 16)
			+ inverse_transparency * ((base_color & 0x00FF0000) >> 16)))
				<< 16
		| ((unsigned int)(transparency * ((added_color & 0x0000FF00) >> 8)
			+ inverse_transparency * ((base_color & 0x0000FF00) >> 8)))
				<< 8
		| (unsigned int)(transparency * (added_color & 0x000000FF)
			+ inverse_transparency * (base_color & 0x000000FF)));
}
