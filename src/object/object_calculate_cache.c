/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_cache.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 06:06:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/13 06:06:00 by vfries           ###   ########lyon.fr   */
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
	return (cone_calculate_cache(object));
}
