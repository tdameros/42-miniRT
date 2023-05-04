#include "struct/t_color.h"

inline unsigned int	rgb_to_uint(const t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

inline t_color	get_t_color_from_uint(const unsigned int color)
{
	return ((t_color){
		.r = (color & 0x00FF0000) >> 16,
		.g = (color & 0x0000FF00) >> 8,
		.b = color & 0x000000FF,
	});
}
