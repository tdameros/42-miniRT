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

#include "math/vector.h"
#include "parsing.h"

size_t	count_spaces_in_line(const char *line);

typedef struct s_mesh
{
	t_vector3f	*vertex;
	t_vector3f	*normals;
	t_vector3f	*faces;
	size_t		nb_vertex;
	size_t		nb_normals;
	size_t		nb_faces;
}	t_mesh;

int	initialize_mesh_with_obj(t_mesh *mesh, const char *file_name)
{
	t_string	file_content;

	file_content = ft_read_file(file_name);
	return (0);
}

size_t	count_vertex(t_string file_content)
{
	size_t	i;

	i = 0;
	return (i);
}

