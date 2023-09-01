#include "ft_vector.h"

void	*ft_vector_get_ptr_to_elem(const t_vector *vector, const size_t index)
{
	if (index >= vector->length)
		return (NULL);
	return (vector->data + index * vector->elem_size);
}
