/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:54:15 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/03 17:54:15 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector2	vector2_add(t_vector2 v1, t_vector2 v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return (v1);
}

t_vector2	vector2_subtract(t_vector2 v1, t_vector2 v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	return (v1);
}

t_vector2	vector2_multiply(t_vector2 v1, double value)
{
	v1.x *= value;
	v1.y *= value;
	return (v1);
}

t_vector2	vector2_divide(t_vector2 v1, double value)
{
	v1.x /= value;
	v1.y /= value;
	return (v1);
}
