#include "struct/t_vector_3d.h"
#include "init.h"

int	get_normalized_vector(char *vector_string, t_vector_3d *vector_destination)
{
	if (get_position(vector_string, vector_destination) < 0)
		return (-1);
	if (vector_destination->x < -1 || vector_destination->x > 1
			|| vector_destination->z < -1 || vector_destination->z > 1
			|| vector_destination->y < -1 || vector_destination->y > 1)
		return (-1);
	return (0);
}
