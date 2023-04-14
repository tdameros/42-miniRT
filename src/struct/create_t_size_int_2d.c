#include "struct/t_size_int_2d.h"

t_size_int_2d	create_t_size_int_2d(int width, int height)
{
	const t_size_int_2d	new_t_size_int_2d = {
		.width = width,
		.height = height
	};

	return (new_t_size_int_2d);
}
