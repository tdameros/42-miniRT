#include "struct/t_color.h"

inline unsigned int	rgb_to_uint(t_color color)
{
	return ((0 << 24) | ((unsigned int) color.r << 16)
		| ((unsigned int) color.g << 8) | ((unsigned int) color.b));
}

inline t_color	get_t_color_from_uint(const unsigned int color)
{
	return ((t_color){
		.r = (int)((color & 0x00FF0000) >> 16),
		.g = (int)((color & 0x0000FF00) >> 8),
		.b = (int)(color & 0x000000FF),
	});
}
