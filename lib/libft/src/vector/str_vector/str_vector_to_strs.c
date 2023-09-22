#include <stdlib.h>

#include "ft_vector.h"
#include "ft_string.h"

static int	fill_result(char **result, t_vector *vector, bool copy);

char	**ft_str_vector_to_strs(t_str_vector *vector, bool copy,
			bool destroy_vector)
{
	char	**result;

	result = malloc(sizeof(char *) * (vector->length + 1));
	if (result == NULL)
	{
		if (destroy_vector)
			ft_str_vector_destroy(vector);
		return (NULL);
	}
	if (fill_result(result, vector, copy) < 0)
	{
		if (destroy_vector)
			ft_str_vector_destroy(vector);
		if (copy)
			ft_free_split(result);
		else
			free(result);
		return (NULL);
	}
	if (copy && destroy_vector)
		ft_str_vector_destroy(vector);
	else if (destroy_vector)
		ft_vector_destroy(vector);
	return (result);
}

static int	fill_result(char **result, t_str_vector *vector, bool copy)
{
	size_t	i;

	i = -1;
	while (++i < vector->length)
	{
		if (copy)
			result[i] = ft_strdup(ft_str_vector_get_elem(vector, i));
		else
			result[i] = ft_str_vector_get_elem(vector, i);
		if (result[i] == NULL)
			return (-1);
	}
	result[i] = NULL;
	return (0);
}
