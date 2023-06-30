/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quatf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 18:43:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/06/28 18:43:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "math/quaternion.h"

t_quaternionf	quaternionf_create(float scalar, t_vector3f vector)
{
	t_quaternionf	quaternion;

	quaternion.scalar = scalar;
	quaternion.vector = vector;
	return (quaternion);
}



