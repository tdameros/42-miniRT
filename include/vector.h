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

typedef struct s_vector2
{
	double	x;
	double	y;
}	t_vector2;

typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}	t_vector3;

typedef struct s_vector4
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_vector4;

//	vector2.c
t_vector2	vector2_create(double x, double y);
void		vector2_print(t_vector2 vector);
t_vector2	vector2_clamp(t_vector2 vector, double min, double max);

//	vector2_math.c
t_vector2	vector2_add(t_vector2 v1, t_vector2 v2);
t_vector2	vector2_subtract(t_vector2 v1, t_vector2 v2);
t_vector2	vector2_multiply(t_vector2 v1, double value);
t_vector2	vector2_divide(t_vector2 v1, double value);

//	vector2_operations.c
double		vector2_length_squared(t_vector2 vector);
double		vector2_length(t_vector2 vector);
t_vector2	vector2_unit(t_vector2 vector);
double		vector2_dot(t_vector2 v1, t_vector2 v2);

//	vector3.c
t_vector3	vector3_create(double x, double y, double z);
void		vector3_print(t_vector3 vector);
t_vector3	vector3_clamp(t_vector3 vector, double min, double max);

//	vector3_math.c
t_vector3	vector3_add(t_vector3 v1, t_vector3 v2);
t_vector3	vector3_subtract(t_vector3 v1, t_vector3 v2);
t_vector3	vector3_multiply(t_vector3 v1, double value);
t_vector3	vector3_divide(t_vector3 v1, double value);

//	vector3_operations.c
double		vector3_length_squared(t_vector3 vector);
double		vector3_length(t_vector3 vector);
t_vector3	vector3_unit(t_vector3 vector);
double		vector3_dot(t_vector3 v1, t_vector3 v2);
t_vector3	vector3_cross(t_vector3 v1, t_vector3 v2);

//	vector3_rotation.c
t_vector3	vector3_rotate_x(t_vector3 vector, double degrees);
t_vector3	vector3_rotate_y(t_vector3 vector, double degrees);
t_vector3	vector3_rotate_z(t_vector3 vector, double degrees);

//	vector4.c
t_vector4	vector4_create(double x, double y, double z, double w);
void		vector4_print(t_vector4 vector);

//	vector4_math.c
t_vector4	vector4_add(t_vector4 v1, t_vector4 v2);
t_vector4	vector4_subtract(t_vector4 v1, t_vector4 v4);
t_vector4	vector4_multiply(t_vector4 v1, double value);
t_vector4	vector4_divide(t_vector4 v1, double value);

//	vector4_operations.c
double		vector4_length_squared(t_vector4 vector);
double		vector4_length(t_vector4 vector);
t_vector4	vector4_unit(t_vector4 vector);
double		vector4_dot(t_vector4 v1, t_vector4 v2);

#endif
