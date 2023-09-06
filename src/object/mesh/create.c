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
#include "vectors.h"

int	mesh_create(t_object *mesh_object, const char *obj_file,
				t_material material)
{
	mesh_object->type = MESH;
	mesh_object->material = material;
	if (initialize_mesh_with_obj(&mesh_object->mesh, obj_file) < 0)
		return (-1);
	mesh_object->name = ft_strdup("Mesh");
	return (0);
}

void	mesh_free(t_mesh *mesh)
{
	vectors3f_free(&mesh->vertex);
	vectors3f_free(&mesh->normals);
	mesh_faces_free(&mesh->faces);
	ft_bzero(mesh, sizeof(*mesh));
}