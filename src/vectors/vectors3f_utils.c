#include <math.h>
#include <float.h>

#include "vectors.h"

t_vector3f	vectors3f_get_min_values(t_vectors3f vectors)
{
	t_vector3f	min_values;
	size_t		i;

	min_values = (t_vector3f){FLT_MAX, FLT_MAX, FLT_MAX};
	i = vectors.length;
	while (i--)
		min_values = (t_vector3f){
			fminf(min_values.x, vectors.data[i].x),
			fminf(min_values.y, vectors.data[i].y),
			fminf(min_values.z, vectors.data[i].z)
		};
	return (min_values);
}

t_vector3f	vectors3f_get_max_values(t_vectors3f vectors)
{
	t_vector3f	max_values;
	size_t		i;

	max_values = (t_vector3f){FLT_MIN, FLT_MIN, FLT_MIN};
	i = vectors.length;
	while (i--)
		max_values = (t_vector3f){
				fmaxf(max_values.x, vectors.data[i].x),
				fmaxf(max_values.y, vectors.data[i].y),
				fmaxf(max_values.z, vectors.data[i].z)
		};
	return (max_values);
}
