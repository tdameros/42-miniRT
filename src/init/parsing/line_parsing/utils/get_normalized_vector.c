/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normalized_vector.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:19:22 by vfries            #+#    #+#             */
/*   Updated: 2023/04/21 03:31:39 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "struct/t_vector_3d.h"
#include "init.h"

int	get_normalized_vector(char *vector_string, t_vector_3d *vector_destination)
{
	if (get_position(vector_string, vector_destination) < 0)
		return (-1);
	if (vector_destination->x < -1 || vector_destination->x > 1
		|| vector_destination->z < -1 || vector_destination->z > 1
		|| vector_destination->y < -1 || vector_destination->y > 1)
		return (-1);
	return (0);
}
