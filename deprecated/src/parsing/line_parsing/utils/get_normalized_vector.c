/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normalized_vector.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:43:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/07 18:43:11 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "math/vector.h"
# include "parsing.h"

int	get_normalized_vector(char *vector_string, t_vector3f *vector_destination)
{
	if (get_position(vector_string, vector_destination) < 0)
		return (-1);
	if (vector_destination->x < -1 || vector_destination->x > 1
		|| vector_destination->z < -1 || vector_destination->z > 1
		|| vector_destination->y < -1 || vector_destination->y > 1)
		return (-1);
	return (0);
}
