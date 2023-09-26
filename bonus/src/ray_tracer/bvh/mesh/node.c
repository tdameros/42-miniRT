/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:58:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/14 20:58:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "float.h"

#include "libft.h"

#include "object.h"
#include "vectors.h"
#include "ray_tracer/bvh.h"

t_mesh_bvh_node	*mesh_bvh_create_node(const t_object *mesh_object)
{
	t_mesh_bvh_node	*node;

	node = malloc(sizeof(*node));
	if (node == NULL)
		return (NULL);
	ft_bzero(node, sizeof(*node));
	node->mesh_object = mesh_object;
	if (vectors_int_initialize(&node->index_faces, 100) < 0)
	{
		free(node);
		return (NULL);
	}
	return (node);
}

t_mesh_bvh_node	*mesh_bvh_create_root(const t_object *mesh_object)
{
	t_mesh_bvh_node		*root_node;
	size_t				i;

	root_node = mesh_bvh_create_node(mesh_object);
	if (root_node == NULL)
		return (NULL);
	i = 0;
	while (i < mesh_object->mesh.faces.length)
	{
		if (vectors_int_add(&root_node->index_faces, (int)i) < 0)
		{
			mesh_bvh_free_node(root_node);
			return (NULL);
		}
		i++;
	}
	root_node->nb_split_triangles = mesh_object->mesh.faces.length;
	mesh_bvh_update_node_bounding_box(root_node);
	return (root_node);
}

void	mesh_bvh_free_node(t_mesh_bvh_node *node)
{
	vectors_int_free(&node->index_faces);
	free(node);
}

void	mesh_bvh_update_node_bounding_box(t_mesh_bvh_node *node)
{
	t_vector3f	min;
	t_vector3f	max;
	size_t		i;

	min = (t_vector3f){FLT_MAX, FLT_MAX, FLT_MAX};
	max = (t_vector3f){-FLT_MAX, -FLT_MAX, -FLT_MAX};
	i = 0;
	while (i < node->index_faces.length)
	{
		min = vector3f_min(min, mesh_get_vertex_from_face(node->mesh_object,
					node->index_faces.data[i], VERTEX_A));
		min = vector3f_min(min, mesh_get_vertex_from_face(node->mesh_object,
					node->index_faces.data[i], VERTEX_B));
		min = vector3f_min(min, mesh_get_vertex_from_face(node->mesh_object,
					node->index_faces.data[i], VERTEX_C));
		max = vector3f_max(max, mesh_get_vertex_from_face(node->mesh_object,
					node->index_faces.data[i], VERTEX_A));
		max = vector3f_max(max, mesh_get_vertex_from_face(node->mesh_object,
					node->index_faces.data[i], VERTEX_B));
		max = vector3f_max(max, mesh_get_vertex_from_face(node->mesh_object,
					node->index_faces.data[i], VERTEX_C));
		i++;
	}
	node->aabb_min = min;
	node->aabb_max = max;
}
