#ifndef LIGHT_H
# define LIGHT_H

# include <stdlib.h>

# include "math/vector.h"
# include "colors.h"

typedef struct s_light
{
	t_vector3f	position;
	float		brightness;
	t_color		color;
}	t_light;

typedef struct s_lights
{
	t_light		*data;
	size_t		length;
	size_t		size;
}	t_lights;

int	initialize_lights_array(t_lights *lights, size_t size);
int	add_light_in_lights(t_lights *lights, t_light light);
int	remove_light_in_lights(t_lights *lights, size_t index);
int	free_lights(t_lights *lights);

#endif
