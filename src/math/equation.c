/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:09:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/06/09 18:09:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>

bool	solve_quadratic_equation(float a, float b, float c, float result[2])
{
	float	delta;

	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (false);
	delta = sqrtf(delta);
	result[0] = (-b + delta) / (2 * a);
	result[1] = (-b - delta) / (2 * a);
	return (true);
}
