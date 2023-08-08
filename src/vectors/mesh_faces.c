/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors3f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:47:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/08/08 11:47:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "vectors.h"

int	mesh_faces_initialize(t_mesh_faces *mesh_faces, size_t size)
{
	if (size == 0)
		size = 1;
	mesh_faces->data = malloc(sizeof(*mesh_faces->data) * size);
	if (mesh_faces->data == NULL)
		return (-1);
	mesh_faces->size = size;
	mesh_faces->length = 0;
	return (0);
}

int	mesh_faces_add(t_mesh_faces *mesh_faces, t_mesh_face mesh_face)
{
	t_mesh_face	*temp;

	if (mesh_faces->length < mesh_faces->size)
		mesh_faces->data[mesh_faces->length] = mesh_face;
	else
	{
		temp = malloc(sizeof(*mesh_faces->data) * (mesh_faces->size * 2));
		if (temp == NULL)
			return (-1);
		ft_memcpy(temp, mesh_faces->data,
			sizeof(*mesh_faces->data) * mesh_faces->size);
		temp[mesh_faces->length] = mesh_face;
		free(mesh_faces->data);
		mesh_faces->data = temp;
		mesh_faces->size *= 2;
	}
	mesh_faces->length += 1;
	return (0);
}

int	mesh_faces_remove(t_mesh_faces *mesh_faces, const size_t index)
{
	if (mesh_faces->length <= index)
		return (-1);
	mesh_faces->data[index] = mesh_faces->data[mesh_faces->length - 1];
	mesh_faces->length -= 1;
	return (0);
}

int	mesh_faces_free(t_mesh_faces *mesh_faces)
{
	free(mesh_faces->data);
	mesh_faces->size = 0;
	mesh_faces->length = 0;
	return (0);
}
