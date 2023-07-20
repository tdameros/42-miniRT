/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modulo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:24:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/15 15:24:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

float	modulof_positive(float dividend, float divisor)
{
	float	result;

	result = fmodf(dividend, divisor);
	if (result < 0)
		result = divisor + result;
	return (result);
}
