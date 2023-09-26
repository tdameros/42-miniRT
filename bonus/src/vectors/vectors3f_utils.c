/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors3f_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:43:38 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/23 22:43:39 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "float.h"

#include "vectors.h"

t_vector3f	vectors3f_get_min_values(t_vectors3f vectors)
{
	t_vector3f	min_values;
	size_t		i;

	min_values = (t_vector3f){FLT_MAX, FLT_MAX, FLT_MAX};
	i = vectors.length;
	while (i--)
		min_values = vector3f_min(min_values, vectors.data[i]);
	return (min_values);
}

t_vector3f	vectors3f_get_max_values(t_vectors3f vectors)
{
	t_vector3f	max_values;
	size_t		i;

	max_values = (t_vector3f){FLT_MIN, FLT_MIN, FLT_MIN};
	i = vectors.length;
	while (i--)
		max_values = vector3f_max(max_values, vectors.data[i]);
	return (max_values);
}
