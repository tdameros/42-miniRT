/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 18:43:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/06/28 18:43:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_H
# define QUATERNION_H

# include "math/matrix.h"

typedef struct s_quaternionf
{
	float		scalar;
	t_vector3f	vector;
}	t_quaternionf;

t_vector3f	quaternionf_rotate_vector3f(float angle, t_vector3f axis,
										  t_vector3f vector);
#endif