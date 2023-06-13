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

typedef struct s_matrix3 {
	float	matrix[3][3];
	int		size;
}	t_matrix3;

typedef struct s_matrix4 {
	float	matrix[4][4];
	int		size;
}	t_matrix4;

//	matrix3.c
t_matrix3	matrix3_create(float value);
t_matrix3	matrix3_create_identity(void);
void		matrix3_print(t_matrix3 matrix);

//	matrix3_math.c
t_vector3f	matrix3_dot_vector3(t_matrix3 matrix, t_vector3f vector);

//	matrix3_rotation.c
t_matrix3	matrix3_rodrigues_rotation(t_vector3f axe, float degrees);

//	matrix4.c
t_matrix4	matrix4_create(float value);
t_matrix4	matrix4_create_identity(void);
void		matrix4_print(t_matrix4 matrix);

//	matrix4_inverse.c
t_matrix4	matrix4_inverse(t_matrix4 matrix);

//	matrix4_math.c
t_matrix4	matrix4_multiply(t_matrix4 m1, t_matrix4 m2);
t_vector4f	matrix4_multiply_vector4(t_matrix4 matrix, t_vector4f vector);


#endif

