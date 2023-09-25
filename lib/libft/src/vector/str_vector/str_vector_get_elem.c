/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_vector_get_elem.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:54:37 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/23 22:54:37 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

char	*ft_str_vector_get_elem(const t_str_vector *str_vector, size_t index)
{
	char	**elem;

	elem = ft_vector_get_ptr_to_elem(str_vector, index);
	if (elem == NULL)
		return (NULL);
	return (*elem);
}
