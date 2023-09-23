/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subdivide.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 23:28:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/19 23:28:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer/bvh.h"

static int	fill_children_nodes(t_mesh_bvh_node *node);
static int	add_obj_index_in_child_node(t_mesh_bvh_node *node,
				size_t face_index, t_side side);
static bool	is_duplicated_node(t_mesh_bvh_node *node);
static void	remove_duplicated_node(t_mesh_bvh_node *node);

int	mesh_bvh_subdivide(t_mesh_bvh_node *node)
{
	if (node == NULL)
		return (0);
	if (node->index_faces.length <= 2)
	{
		node->is_leaf = true;
		return (0);
	}
	if (fill_children_nodes(node) < 0)
		return (-1);
	node->left_node->previous_node = node;
	node->right_node->previous_node = node;
	node->nb_split_triangles = node->index_faces.length;
	if (is_duplicated_node(node))
	{
		remove_duplicated_node(node);
		return (0);
	}
	vectors_int_free(&node->index_faces);
	mesh_bvh_update_node_bounding_box(node->left_node);
	mesh_bvh_update_node_bounding_box(node->right_node);
	if (mesh_bvh_subdivide(node->left_node) < 0)
		return (-1);
	if (mesh_bvh_subdivide(node->right_node) < 0)
		return (-1);
	return (0);
}

static int	fill_children_nodes(t_mesh_bvh_node *node)
{
	const t_aabb_split		split = split_bounding_box_mesh_node(node);
	t_side					side;
	size_t					i;
	size_t					face_index;

	node->left_node = mesh_bvh_create_node(node->mesh_object);
	node->right_node = mesh_bvh_create_node(node->mesh_object);
	if (node->left_node == NULL || node->right_node == NULL)
		return (-1);
	i = 0;
	while (i < node->index_faces.length)
	{
		face_index = node->index_faces.data[i];
		side = get_face_side(node, (int)face_index, split);
		if (add_obj_index_in_child_node(node, face_index, side) < 0)
			return (-1);
		i++;
	}
	return (0);
}

static int	add_obj_index_in_child_node(t_mesh_bvh_node *node,
										size_t face_index, t_side side)
{
	if (side == LEFT_AND_RIGHT || side == LEFT)
	{
		if (vectors_int_add(&node->left_node->index_faces, face_index) < 0)
			return (-1);
	}
	if (side == LEFT_AND_RIGHT || side == RIGHT)
	{
		if (vectors_int_add(&node->right_node->index_faces, face_index) < 0)
			return (-1);
	}
	return (0);
}

static bool	is_duplicated_node(t_mesh_bvh_node *node)
{
	return (node->left_node->index_faces.length \
		== node->nb_split_triangles \
		|| node->right_node->index_faces.length \
		== node->nb_split_triangles);
}

static void	remove_duplicated_node(t_mesh_bvh_node *node)
{
	mesh_bvh_free_node(node->left_node);
	mesh_bvh_free_node(node->right_node);
	node->left_node = NULL;
	node->right_node = NULL;
	node->is_leaf = true;
}
