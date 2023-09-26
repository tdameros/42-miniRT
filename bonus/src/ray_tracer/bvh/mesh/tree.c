/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 23:42:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/19 23:42:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer/bvh.h"

t_mesh_bvh_node	*mesh_bvh_create_tree(const t_object *mesh_object)
{
	t_mesh_bvh_node	*root_node;

	root_node = mesh_bvh_create_root(mesh_object);
	if (root_node == NULL)
		return (NULL);
	if (mesh_bvh_subdivide(root_node) < 0)
	{
		mesh_bvh_free_tree(root_node);
		return (NULL);
	}
	return (root_node);
}

void	mesh_bvh_free_tree(t_mesh_bvh_node *root_node)
{
	if (root_node == NULL)
		return ;
	if (root_node->left_node != NULL)
		mesh_bvh_free_tree(root_node->left_node);
	if (root_node->right_node != NULL)
		mesh_bvh_free_tree(root_node->right_node);
	mesh_bvh_free_node(root_node);
}

void	mesh_bvh_update_tree(const t_object *mesh_object, t_mesh_bvh_node *tree)
{
	if (tree == NULL)
		return ;
	tree->mesh_object = mesh_object;
	if (tree->left_node != NULL)
		mesh_bvh_update_tree(mesh_object, tree->left_node);
	if (tree->right_node != NULL)
		mesh_bvh_update_tree(mesh_object, tree->right_node);
}
