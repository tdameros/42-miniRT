/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_vector_destroy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:54:31 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/25 20:07:34 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_vector.h"

void	ft_str_vector_destroy(t_str_vector *str_vector)
{
	size_t	i;

	i = str_vector->length;
	while (i--)
		free(ft_str_vector_get_elem(str_vector, i));
	ft_vector_destroy(str_vector);
}
