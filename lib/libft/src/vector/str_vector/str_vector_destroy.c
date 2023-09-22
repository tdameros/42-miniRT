#include <stdlib.h>

#include "ft_vector.h"

void	ft_str_vector_destroy(t_str_vector *str_vector)
{
	while (str_vector->length--)
		free(ft_str_vector_get_elem(str_vector, str_vector->length));
	ft_vector_destroy(str_vector);
}
