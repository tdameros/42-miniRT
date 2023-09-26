/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_cache.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 08:28:50 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/26 15:55:14 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

void	object_calculate_cache(t_object *object)
{
	if (object->type == SPHERE)
		return (sphere_calculate_cache(object));
	if (object->type == PLANE)
		return (plane_calculate_cache(object));
	if (object->type == CYLINDER)
		return (cylinder_calculate_cache(object));
}
