/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 08:15:52 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/31 08:15:53 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>

#include "math/equation.h"

bool	solve_quadratic_equation(t_quadf_equation *equation)
{
	float	delta_sqrt;

	equation->delta = equation->b * equation->b
		- 4.f * equation->a * equation->c;
	if (equation->delta <= 0.f)
		return (false);
	if (equation->delta == 0.f)
	{
		equation->s1 = -equation->b / (2.f * equation->a);
		equation->s2 = -equation->b / (2.f * equation->a);
		return (true);
	}
	delta_sqrt = sqrtf(equation->delta);
	equation->s1 = (-equation->b + delta_sqrt) / (2.f * equation->a);
	equation->s2 = (-equation->b - delta_sqrt) / (2.f * equation->a);
	return (true);
}
