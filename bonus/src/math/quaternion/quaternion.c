/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 08:21:33 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/31 08:21:34 by tdameros         ###   ########lyon.fr   */
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
