/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_in_obj_file.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:31:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/06 21:31:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <math.h>

#include "mesh.h"
#include "math/vector.h"
#include "parsing.h"
#include "vectors.h"

static int	parse_vertex_line(t_mesh *mesh, char **split_line);
static int	parse_normal_line(t_mesh *mesh, char **split_line);
static int	parse_face_line(t_mesh *mesh, char **split_line);
static int	parse_face_vertex(t_mesh *mesh, t_vector2i *face,
				char *vertex_face);

int	parse_line_in_obj_file(t_mesh *mesh, const char *line)
{
	char	**split_line;
	size_t	len;
	int		return_code;

	return_code = 1;
	split_line = ft_split(line, ' ');
	if (split_line == NULL)
		return (-1);
	len = ft_split_len(split_line);
	if (len == 4 && ft_strcmp(split_line[0], "v") == 0)
		return_code = parse_vertex_line(mesh, split_line);
	else if (len == 4 && ft_strcmp(split_line[0], "vn") == 0)
		return_code = parse_normal_line(mesh, split_line);
	else if (len == 4 && ft_strcmp(split_line[0], "f") == 0)
		return_code = parse_face_line(mesh, split_line);
	ft_free_split(split_line);
	return (return_code);
}

static int	parse_vertex_line(t_mesh *mesh, char **split_line)
{
	t_vector3f	new_vertex;

	errno = 0;
	new_vertex.x = ft_atof(split_line[1]);
	new_vertex.y = ft_atof(split_line[2]);
	new_vertex.z = ft_atof(split_line[3]);
	if (errno != 0)
		return (0);
	if (vectors3f_add(&mesh->base_vertex, new_vertex) < 0)
		return (-1);
	mesh->vertex_min = (t_vector3f){fminf(new_vertex.x, mesh->vertex_min.x), \
									fminf(new_vertex.y, mesh->vertex_min.y), \
									fminf(new_vertex.z, mesh->vertex_min.z)};
	mesh->vertex_max = (t_vector3f){fmaxf(new_vertex.x, mesh->vertex_max.x), \
									fmaxf(new_vertex.y, mesh->vertex_max.y), \
									fmaxf(new_vertex.z, mesh->vertex_max.z)};
	return (1);
}

static int	parse_normal_line(t_mesh *mesh, char **split_line)
{
	t_vector3f	new_normal;

	errno = 0;
	new_normal.x = ft_atof(split_line[1]);
	new_normal.y = ft_atof(split_line[2]);
	new_normal.z = ft_atof(split_line[3]);
	if (errno != 0)
		return (0);
	if (vectors3f_add(&mesh->base_normals, new_normal) < 0)
		return (-1);
	return (1);
}

static int	parse_face_line(t_mesh *mesh, char **split_line)
{
	t_mesh_face	face;
	int			status_code;

	status_code = parse_face_vertex(mesh, &face.vertex_a, split_line[1]);
	if (status_code <= 0)
		return (status_code);
	status_code = parse_face_vertex(mesh, &face.vertex_b, split_line[2]);
	if (status_code <= 0)
		return (status_code);
	status_code = parse_face_vertex(mesh, &face.vertex_c, split_line[3]);
	if (status_code <= 0)
		return (status_code);
	return (mesh_faces_add(&mesh->faces, face));
}

static int	parse_face_vertex(t_mesh *mesh, t_vector2i *face, char *vertex_face)
{
	char	**split_face;
	size_t	len;

	split_face = ft_split(vertex_face, '/');
	if (split_face == NULL)
		return (-1);
	len = ft_split_len(split_face);
	if (len != 2 && len != 3)
	{
		ft_free_split(split_face);
		return (0);
	}
	errno = 0;
	face->x = ft_atoi(split_face[0]);
	if (len == 3)
		face->y = ft_atoi(split_face[2]);
	else
		face->y = ft_atoi(split_face[1]);
	ft_free_split(split_face);
	if (errno != 0)
		return (0);
	if (face->x > (int)mesh->base_vertex.length
		|| face->y > (int)mesh->base_normals.length)
		return (0);
	return (1);
}
