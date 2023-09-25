/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_vector_destroy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:54:31 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/23 22:54:32 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_vector.h"

void	ft_str_vector_destroy(t_str_vector *str_vector)
{
	while (str_vector->length--)
		free(ft_str_vector_get_elem(str_vector, str_vector->length));
	ft_vector_destroy(str_vector);
}
