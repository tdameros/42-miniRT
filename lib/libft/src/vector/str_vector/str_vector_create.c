#include "ft_vector.h"

int	ft_str_vector_create(t_str_vector *vector, const size_t size)
{
	return (ft_vector_create(vector, sizeof(char *), size));
}
