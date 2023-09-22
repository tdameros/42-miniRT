#include "libft.h"

#include "math/vector.h"
#include "parsing.h"

int	get_rotation(const char *rotation_string, t_vector3f *rotation_destination)
{
	if (get_vector3f(rotation_string, rotation_destination) < 0)
		return (-1);
	if (rotation_destination->x < 0.f || rotation_destination->x >= 360.f
		|| rotation_destination->y < 0.f || rotation_destination->y >= 360.f
		|| rotation_destination->z < 0.f || rotation_destination->z >= 360.f)
		return (-1);
	return (0);
}
