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

# define VECTOR_ALLOCATION_FAILED -1
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

typedef t_vector	t_str_vector;

// str_vector/str_vector_add_elem.c
int		ft_str_vector_add_elem(t_str_vector *vector, char *elem);

//	str_vector/str_vector_create.c
int		ft_str_vector_create(t_str_vector *vector, const size_t size);

//	str_vector/str_vector_delete_elem.c
void	ft_str_vector_delete_elem(t_str_vector *str_vector, const size_t index,
			const bool keep_same_order);

//	str_vector/str_vector_destroy.c
void	ft_str_vector_destroy(t_str_vector *str_vector);

//	str_vector/str_vector_get_elem.c
char	*ft_str_vector_get_elem(const t_str_vector *str_vector, size_t index);

//	str_vector/str_vector_to_strs.c
char	**ft_str_vector_to_strs(t_str_vector *vector, bool copy,
			bool destroy_vector);

//	vector_add_elem.c
int		ft_vector_add_elem(t_vector *vector, const void *new_elem);

//	vector_append.c
int		ft_vector_append(t_vector *dst, const t_vector *src);

//	vector_change_size.c
int		ft_vector_change_size(t_vector *vector, size_t size);

//	vector_convert_to_array.c
void	*ft_vector_convert_to_array(t_vector *vector, size_t *size,
			bool make_copy, bool destroy_vector);

//	vector_create.c
int		ft_vector_create(t_vector *vector, size_t elem_size,
			size_t size);

//	vector_delete_elem.c
void	ft_vector_delete_elem(t_vector *vector, size_t index,
			bool keep_same_order);

//	vector_destroy.c
void	ft_vector_destroy(t_vector *vector);

//	vector_get_ptr_to_elem.c
void	*ft_vector_get_ptr_to_elem(const t_vector *vector, const size_t index);

//	vector_minimize_size.c
int		ft_vector_minimize_size(t_vector *vector);

#endif
