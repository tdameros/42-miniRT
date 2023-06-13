/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:33:43 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/06 17:33:45 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vector2i
{
	int	x;
	int	y;
}	t_vector2i;

typedef struct s_vector2f
{
	float	x;
	float	y;
}	t_vector2f;

typedef struct s_vector3f
{
	float	x;
	float	y;
	float	z;
}	t_vector3f;

typedef struct s_vector4f
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vector4f;

//	vector2.c
t_vector2f	vector2f_create(float x, float y);
void		vector2f_print(t_vector2f vector);
t_vector2f	vector2f_clamp(t_vector2f vector, float min, float max);

//	vector2_math.c
t_vector2f	vector2f_add(t_vector2f v1, t_vector2f v2);
t_vector2f	vector2f_subtract(t_vector2f v1, t_vector2f v2);
t_vector2f	vector2f_multiply(t_vector2f v1, float value);
t_vector2f	vector2f_divide(t_vector2f v1, float value);

//	vector2_operations.c
float		vector2f_length_squared(t_vector2f vector);
float		vector2f_length(t_vector2f vector);
t_vector2f	vector2f_unit(t_vector2f vector);
float		vector2f_dot(t_vector2f v1, t_vector2f v2);

//	vector3.c
t_vector3f	vector3f_create(float x, float y, float z);
void		vector3f_print(t_vector3f vector);
t_vector3f	vector3f_clamp(t_vector3f vector, float min, float max);

//	vector3_math.c
t_vector3f	vector3f_add(t_vector3f v1, t_vector3f v2);
t_vector3f	vector3f_subtract(t_vector3f v1, t_vector3f v2);
t_vector3f	vector3f_multiply(t_vector3f v1, float value);
t_vector3f	vector3f_divide(t_vector3f v1, float value);

//	vector3_operations.c
float		vector3f_length_squared(t_vector3f vector);
float		vector3f_length(t_vector3f vector);
t_vector3f	vector3f_unit(t_vector3f vector);
float		vector3f_dot(t_vector3f v1, t_vector3f v2);
t_vector3f	vector3f_cross(t_vector3f v1, t_vector3f v2);

//	vector3_rotation.c
t_vector3f	vector3f_rotate_x(t_vector3f vector, float degrees);
t_vector3f	vector3f_rotate_y(t_vector3f vector, float degrees);
t_vector3f	vector3f_rotate_z(t_vector3f vector, float degrees);

//	vector4.c
t_vector4f	vector4f_create(float x, float y, float z, float w);
void		vector4f_print(t_vector4f vector);

//	vector4_math.c
t_vector4f	vector4f_add(t_vector4f v1, t_vector4f v2);
t_vector4f	vector4f_subtract(t_vector4f v1, t_vector4f v4);
t_vector4f	vector4f_multiply(t_vector4f v1, float value);
t_vector4f	vector4f_divide(t_vector4f v1, float value);

//	vector4_operations.c
float		vector4f_length_squared(t_vector4f vector);
float		vector4f_length(t_vector4f vector);
t_vector4f	vector4f_unit(t_vector4f vector);
float		vector4f_dot(t_vector4f v1, t_vector4f v2);

#endif
