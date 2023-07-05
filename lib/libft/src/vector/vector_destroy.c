/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:57:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/14 19:57:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_vector.h"
#include "ft_mem.h"

void	ft_vector_destroy(t_vector *vector)
{
	free(vector->data);
	ft_bzero(vector, sizeof(*vector));
}
