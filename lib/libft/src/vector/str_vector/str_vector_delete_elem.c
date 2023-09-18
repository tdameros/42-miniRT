#include <stdlib.h>

#include "ft_vector.h"

void	ft_str_vector_delete_elem(t_vector *str_vector, const size_t index,
			const bool keep_same_order)
{
	free(ft_str_vector_get_elem(str_vector, index));
	ft_vector_delete_elem(str_vector, index, keep_same_order);
}
