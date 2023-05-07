/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:35:37 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/06 17:35:38 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"

typedef struct s_matrix4 {
	double	matrix[4][4];
	int		size;
}	t_matrix4;


//	matrix4.c
t_matrix4	matrix4_create(double value);
t_matrix4	matrix4_create_identity(void);
void		matrix4_print(t_matrix4 matrix);

//	matrix4_inverse.c
t_matrix4	matrix4_inverse(t_matrix4 matrix);

//	matrix4_math.c
t_matrix4	matrix4_multiply(t_matrix4 m1, t_matrix4 m2);
t_vector4	matrix4_multiply_vector4(t_matrix4 matrix, t_vector4 vector);


#endif

