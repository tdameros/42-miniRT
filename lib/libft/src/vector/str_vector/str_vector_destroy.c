#include <stdlib.h>

#include "ft_vector.h"

void	ft_str_vector_destroy(t_vector *str_vector)
{
	while (str_vector->size--)
		free(ft_str_vector_get_elem(str_vector, str_vector->size));
	ft_vector_destroy(str_vector);
}
