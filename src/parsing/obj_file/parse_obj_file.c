/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 18:46:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/08/07 18:46:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "mesh.h"
#include "parsing.h"
#include "vectors.h"

static int	initialize_vectors_in_mesh(t_mesh *mesh);
static int	parse_obj_file(t_mesh *mesh, t_string file_content);

int	initialize_mesh_with_obj(t_mesh *mesh, const char *file_name)
{
	t_string	file_content;

	file_content = ft_read_file(file_name);
	if (file_content.data == NULL)
		return (-1);
	if (initialize_vectors_in_mesh(mesh) < 0)
	{
		free(file_content.data);
		return (-1);
	}
	if (parse_obj_file(mesh, file_content) < 0)
	{
		free(file_content.data);
		mesh_free(mesh);
		return (-1);
	}
	free(file_content.data);
	if (mesh->faces.length == 0)
	{
		mesh_free(mesh);
		return (NO_VALID_FACES_FOUND);
	}
	return (0);
}

static int	initialize_vectors_in_mesh(t_mesh *mesh)
{
	if (vectors3f_initialize(&mesh->base_vertex, 100) < 0)
		return (-1);
	if (vectors3f_initialize(&mesh->base_normals, 100) < 0)
	{
		vectors3f_free(&mesh->base_vertex);
		return (-1);
	}
	if (mesh_faces_initialize(&mesh->faces, 100) < 0)
	{
		vectors3f_free(&mesh->base_vertex);
		vectors3f_free(&mesh->base_normals);
		return (-1);
	}
	return (0);
}

static int	parse_obj_file(t_mesh *mesh, t_string file_content)
{
	size_t	i;
	char	**lines;

	mesh->vertex_max = (t_vector3f){FLT_MIN, FLT_MIN, FLT_MIN};
	mesh->vertex_min = (t_vector3f){FLT_MAX, FLT_MAX, FLT_MAX};
	i = 0;
	lines = ft_split(file_content.data, '\n');
	if (lines == NULL)
		return (-1);
	while (lines[i] != NULL)
	{
		if (parse_line_in_obj_file(mesh, lines[i]) < 0)
		{
			ft_free_split(lines);
			return (-1);
		}
		i++;
	}
	ft_free_split(lines);
	return (0);
}

