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

#include "math/vector.h"

t_vector2f	vector2f_add(t_vector2f v1, t_vector2f v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return (v1);
}

t_vector2f	vector2f_subtract(t_vector2f v1, t_vector2f v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	return (v1);
}

t_vector2f	vector2f_multiply(t_vector2f v1, float value)
{
	v1.x *= value;
	v1.y *= value;
	return (v1);
}

t_vector2f	vector2f_divide(t_vector2f v1, float value)
{
	v1.x /= value;
	v1.y /= value;
	return (v1);
}
