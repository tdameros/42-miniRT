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

static char	*get_obj_name(const char *obj_file);

/*
 * Return code:
 * 1 mesh object has been successful initialize
 * 0 obj_file is empty
 * -1 an error has been encountered
 */
int	mesh_object_initialize(t_object *mesh_object, const char *obj_file,
				t_material material)
{
	int	return_code;


	mesh_object->type = MESH;
	mesh_object->material = material;
	return_code = initialize_mesh_with_obj(&mesh_object->mesh, obj_file);
	if (return_code < 0)
		return (-1);
	else if (return_code == 0)
		return (0);
	mesh_object->name = get_obj_name(obj_file);
	if (mesh_object->name == NULL)
	{
		mesh_free(&mesh_object->mesh);
		return (-1);
	}
	return (1);
}

static char	*get_obj_name(const char *obj_file)
{
	char	*obj_file_without_full_path;
	char	*obj_name;

	obj_file_without_full_path = ft_strrchr(obj_file, '/');
	if (obj_file_without_full_path != NULL)
	{
		obj_file_without_full_path++;
		obj_name = ft_substr(obj_file_without_full_path, 0,
				ft_strlen(obj_file_without_full_path) - 4);
	}
	else
		obj_name = ft_substr(obj_file, 0, ft_strlen(obj_file) - 4);
	if (obj_name != NULL)
		obj_name[0] = ft_toupper(obj_name[0]);
	return (obj_name);
}

void	mesh_free(t_mesh *mesh)
{
	vectors3f_free(&mesh->vertex);
	vectors3f_free(&mesh->normals);
	mesh_faces_free(&mesh->faces);
	ft_bzero(mesh, sizeof(*mesh));
}