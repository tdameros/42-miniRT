/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 08:08:49 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/31 08:08:49 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "export.h"

int	write_object(const t_object object, int fd)
{
	if (object.type == SPHERE)
		return (write_sphere(object, fd));
	else if (object.type == PLANE)
		return (write_plane(object, fd));
	else if (object.type == CYLINDER)
		return (write_cylinder(object, fd));
	else if (object.type == CONE)
		return (write_cone(object, fd));
	else if (object.type == MESH)
		return (write_mesh_object(object, fd));
	return (-1);
}
