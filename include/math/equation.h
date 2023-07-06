/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:16:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/06/09 18:16:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUATION_H
# define EQUATION_H

# include <stdbool.h>

typedef struct s_quadf_equation
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	s1;
	float	s2;
}	t_quadf_equation;

//bool	solve_quadratic_equation(float a, float b, float c, float result[2]);
bool	solve_quadratic_equation(t_quadf_equation *equation);

#endif