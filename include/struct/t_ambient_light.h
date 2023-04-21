#ifndef T_AMBIENT_LIGHT_H
#define T_AMBIENT_LIGHT_H

#include "struct/t_vector_3d.h"
#include "struct/t_color.h"

typedef struct s_ambient_light
{
	double	lighting_ratio;
	t_color	color;
}	t_ambient_light;

#endif //T_AMBIENT_LIGHT_H
