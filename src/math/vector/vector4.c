/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:57:18 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/03 17:59:11 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "math/vector.h"

t_vector4f	vector4f_create(float x, float y, float z, float w)
{
	t_vector4f	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	vector.w = w;
	return (vector);
}

void	vector4f_print(t_vector4f vector)
{
	printf("Vector4 => x:%f y:%f z:%f w:%f\n",
		vector.x,
		vector.y,
		vector.z,
		vector.w);
}
