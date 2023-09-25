/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_get_ptr_to_elem.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:56:13 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/23 22:56:14 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

void	*ft_vector_get_ptr_to_elem(const t_vector *vector, const size_t index)
{
	if (index >= vector->length)
		return (NULL);
	return (vector->data + index * vector->elem_size);
}
