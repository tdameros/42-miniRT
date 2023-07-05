/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:46:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/14 18:46:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

# include <stddef.h>
# include <stdbool.h>

# define VECTOR_ALLOCATION_FAILED (-1)
# define VECTOR_SIZE_TOO_SMALL 1
# define VECTOR_VECTORS_ELEM_SIZE_DONT_MATCH 2
# define VECTOR_SUCCESS 0

typedef struct s_vector
{
	void	*data;
	size_t	length;
	size_t	size;
	size_t	elem_size;
}	t_vector;

int		ft_vector_add_elem(t_vector *vector, const void *new_elem);

int		ft_vector_append(t_vector *dst, const t_vector *src);

int		ft_vector_change_size(t_vector *vector, size_t size);

void	*ft_vector_convert_to_array(t_vector *vector, size_t *size,
			bool make_copy, bool destroy_vector);

int		ft_vector_create(t_vector *vector, size_t elem_size,
			size_t size);

void	ft_vector_delete_elem(t_vector *vector, size_t index,
			bool keep_same_order);

void	ft_vector_destroy(t_vector *vector);

int		ft_vector_minimize_size(t_vector *vector);

#endif