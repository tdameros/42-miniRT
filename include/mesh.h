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



typedef struct s_mesh
{
	t_vectors3f		vertex;
	t_vectors3f		normals;
	t_mesh_faces	faces;
}	t_mesh;

int	initialize_mesh_with_obj(t_mesh *mesh, const char *file_name);
#endif