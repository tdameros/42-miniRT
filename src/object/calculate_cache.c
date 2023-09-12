/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_cache.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 08:28:50 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/31 08:28:53 by tdameros         ###   ########lyon.fr   */
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
	if (object->type == CONE)
		return (cone_calculate_cache(object));
	if (object->type == MESH)
		return (mesh_object_update_vertex(object));
}
