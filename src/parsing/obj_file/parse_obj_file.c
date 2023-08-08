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

#include <errno.h>

#include "mesh.h"
#include "math/vector.h"
#include "parsing.h"
#include "vectors.h"


size_t	count_spaces_in_line(const char *line);
int		parse_vertex_line(t_mesh *mesh, char **split_line);
int		parse_line(t_mesh *mesh, const char *line);
int		parse_normal_line(t_mesh *mesh, char **split_line);
int		parse_face_vertex(t_mesh *mesh, t_vector2i *face, char *vertex_face);
int		parse_face_line(t_mesh *mesh, char **split_line);

#include <stdio.h>
int	initialize_mesh_with_obj(t_mesh *mesh, const char *file_name)
{
	t_string	file_content;
	char 		*file_content_with_end;
	char		**lines;
	size_t		i;

	file_content = ft_read_file(file_name);
	if (file_content.data == NULL)
		return (-1);
	file_content_with_end = malloc((file_content.len + 1) * sizeof(*file_content_with_end));
	if (file_content_with_end == NULL)
		return (-1);
	ft_memcpy(file_content_with_end, file_content.data, file_content.len);
	file_content_with_end[file_content.len] = '\0';
	vectors3f_initialize(&mesh->vertex, 100);
	vectors3f_initialize(&mesh->normals, 100);
	mesh_faces_initialize(&mesh->faces, 100);
	lines = ft_split(file_content_with_end, '\n');
	i = 0;
	while (lines[i] != NULL)
	{
		parse_line(mesh, lines[i]);
		i++;
	}
	ft_free_split(lines);
	return (0);
}

int	parse_line(t_mesh *mesh, const char *line)
{
	char	**split_line;
	size_t	len;


	split_line = ft_split(line, ' ');
	if (split_line == NULL)
		return (-1);
	len = ft_split_len(split_line);
	if (len == 4 && ft_strcmp(split_line[0], "v") == 0)
	{
		parse_vertex_line(mesh, split_line);
	}
	else if (len == 4 && ft_strcmp(split_line[0], "vn") == 0)
	{
		parse_normal_line(mesh, split_line);
	}
	else if (len == 4 && ft_strcmp(split_line[0], "f") == 0)
	{
		parse_face_line(mesh, split_line);
	}
	ft_free_split(split_line);
	return (0);
}

int	parse_vertex_line(t_mesh *mesh, char **split_line)
{
	t_vector3f	new_vertex;

	errno = 0;
	new_vertex.x = ft_atof(split_line[1]);
	new_vertex.y = ft_atof(split_line[2]);
	new_vertex.z = ft_atof(split_line[3]);
	if (errno != 0)
		return (0);
	if (vectors3f_add(&mesh->vertex, new_vertex) < 0)
		return (-1);
	return (1);
}

int	parse_normal_line(t_mesh *mesh, char **split_line)
{
	t_vector3f	new_normal;

	errno = 0;
	new_normal.x = ft_atof(split_line[1]);
	new_normal.y = ft_atof(split_line[2]);
	new_normal.z = ft_atof(split_line[3]);
	if (errno != 0)
		return (0);
	if (vectors3f_add(&mesh->normals, new_normal) < 0)
		return (-1);
	return (1);
}

int	parse_face_line(t_mesh *mesh, char **split_line)
{
	t_mesh_face	face;

	if (parse_face_vertex(mesh, &face.vertex_a, split_line[1]) <= 0)
		return (0);
	if (parse_face_vertex(mesh, &face.vertex_b, split_line[2]) <= 0)
		return (0);
	if (parse_face_vertex(mesh, &face.vertex_c, split_line[3]) <= 0)
		return (0);
	mesh_faces_add(&mesh->faces, face);
	return (1);
}

int	parse_face_vertex(t_mesh *mesh, t_vector2i *face, char *vertex_face)
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
	if (face->x > (int)mesh->vertex.length)
		return (0);
	if (face->y > (int)mesh->normals.length)
		return (0);
	return (1);
}