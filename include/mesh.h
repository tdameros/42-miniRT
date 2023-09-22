/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:47:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/08/08 13:47:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
# define MESH_H

# include "vectors.h"
# include "libft.h"

# define NO_VALID_FACES_FOUND -2

# define MESH_MINIMUM_SCALE 0.001f

typedef struct s_mesh
{
	t_vectors3f		base_vertex;
	t_vector3f		vertex_min;
	t_vector3f		vertex_max;
	t_vectors3f		base_normals;
	t_mesh_faces	faces;
	struct s_mesh_bvh_node	*tree;
}	t_mesh;

typedef struct s_size_to_allocate_in_mesh
{
	size_t	*number_of_vertex;
	size_t	*number_of_normals;
	size_t	*number_of_faces;
}	t_size_to_allocate_in_mesh;

t_str_vector	get_relevent_obj_lines(const char *file_name,
					size_t *number_of_vertex, size_t *number_of_normals,
					size_t *number_of_faces);
int				initialize_mesh_with_obj(t_mesh *mesh, const char *file_name);
int				parse_line_in_obj_file(t_mesh *mesh, const char *line);

#endif
