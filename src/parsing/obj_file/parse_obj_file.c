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

#include <math.h>

#include "mesh.h"
#include "parsing.h"
#include "vectors.h"

static int	initialize_vectors_in_mesh(t_mesh *mesh, size_t number_of_vertex,
				size_t number_of_normals, size_t number_of_faces);
static int	parse_obj_file(t_mesh *mesh, t_str_vector lines);

int	initialize_mesh_with_obj(t_mesh *mesh, const char *file_name)
{
	size_t			number_of_vertex;
	size_t			number_of_normals;
	size_t			number_of_faces;
	t_str_vector	lines;

	lines = get_relevent_obj_lines(file_name, &number_of_vertex,
			&number_of_normals, &number_of_faces);
	if (lines.length == 0)
		return (-1);
	if (initialize_vectors_in_mesh(mesh, number_of_vertex, number_of_normals,
			number_of_faces) < 0)
	{
		ft_str_vector_destroy(&lines);
		return (-1);
	}
	if (parse_obj_file(mesh, lines) < 0)
	{
		ft_str_vector_destroy(&lines);
		mesh_free(mesh);
		return (-1);
	}
	ft_str_vector_destroy(&lines);
	if (mesh->faces.length == 0)
	{
		mesh_free(mesh);
		return (NO_VALID_FACES_FOUND);
	}
	return (0);
}

static int	initialize_vectors_in_mesh(t_mesh *mesh, size_t number_of_vertex,
				size_t number_of_normals, size_t number_of_faces)
{
	if (vectors3f_initialize(&mesh->base_vertex, number_of_vertex) < 0)
		return (-1);
	if (vectors3f_initialize(&mesh->base_normals, number_of_normals) < 0)
	{
		vectors3f_free(&mesh->base_vertex);
		return (-1);
	}
	if (mesh_faces_initialize(&mesh->faces, number_of_faces) < 0)
	{
		vectors3f_free(&mesh->base_vertex);
		vectors3f_free(&mesh->base_normals);
		return (-1);
	}
	return (0);
}

static int	parse_obj_file(t_mesh *mesh, t_str_vector lines)
{
	char	**limit = (char **)lines.data + lines.length;
	char	**cursor = lines.data;

	mesh->vertex_max = (t_vector3f){-INFINITY, -INFINITY, -INFINITY};
	mesh->vertex_min = (t_vector3f){INFINITY, INFINITY, INFINITY};
	while (cursor < limit)
		if (parse_line_in_obj_file(mesh, *cursor++) < 0)
			return (-1);
	return (0);
}
