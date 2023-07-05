/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_minimize_size.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:09:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/14 20:09:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

int	ft_vector_minimize_size(t_vector *vector)
{
	return (ft_vector_change_size(vector, vector->length));
}
