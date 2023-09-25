/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 08:16:50 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/31 08:16:51 by tdameros         ###   ########lyon.fr   */
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

//	equation.c
bool	solve_quadratic_equation(t_quadf_equation *equation);

#endif
