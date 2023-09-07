#include <stdint.h>

#include "math/vector.h"
#include "colors.h"

inline unsigned int	rgb_to_uint(const t_color color)
{
	return (((unsigned int) color.x << 16)
		| ((unsigned int) color.y << 8)
		| (unsigned int) color.z);
}

inline unsigned int	vec_rgb_to_uint(const t_vector3f color)
{
	return (((unsigned int)color.x << 16) | ((unsigned int)color.y << 8)
		| (unsigned int)color.z);
}

inline uint8_t	get_transparency(const unsigned int color)
{
	return ((color & 0xFF000000) >> 24);
}

inline float	get_transparency_ratio(const unsigned int color)
{
	return (get_transparency(color) / 255.f);
}

inline t_color	get_t_color_from_uint(const unsigned int color)
{
	return ((t_color){
		.x = (color & 0x00FF0000) >> 16,
		.y = (color & 0x0000FF00) >> 8,
		.z = color & 0x000000FF,
	});
}
