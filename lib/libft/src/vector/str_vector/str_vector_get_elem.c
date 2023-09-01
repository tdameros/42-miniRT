#include "ft_vector.h"

char	*ft_str_vector_get_elem(const t_vector *str_vector, size_t index)
{
	char	**elem;

	elem = ft_vector_get_ptr_to_elem(str_vector, index);
	if (elem == NULL)
		return (NULL);
	return (*elem);
}
