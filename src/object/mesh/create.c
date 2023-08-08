/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:34:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/08/08 18:34:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "object.h"

t_object	mesh_create(const char *obj_file, t_material material)
{
	t_object	mesh;

	mesh.type = MESH;
	mesh.material = material;
	mesh.name = ft_strdup("Mesh");
	initialize_mesh_with_obj(&mesh.mesh, obj_file);
	return (mesh);
}
