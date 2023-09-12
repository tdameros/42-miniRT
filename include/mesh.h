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

# define NO_VALID_FACES_FOUND -2

typedef struct s_mesh
{
	t_vectors3f		base_vertex;
	t_vector3f		vertex_min;
	t_vector3f		vertex_max;
	t_vectors3f		base_normals;
	t_mesh_faces	faces;
}	t_mesh;

int	initialize_mesh_with_obj(t_mesh *mesh, const char *file_name);
int	parse_line_in_obj_file(t_mesh *mesh, const char *line);

#endif