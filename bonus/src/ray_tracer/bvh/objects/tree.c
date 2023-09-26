/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 23:05:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/15 23:05:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer/bvh.h"

t_objects_bvh_node	*objects_bvh_create_tree(const t_objects *objects)
{
	t_objects_bvh_node	*root_node;

	root_node = objects_bvh_create_root(objects);
	if (root_node == NULL)
		return (NULL);
	objects_bvh_update_node_bounding_box(root_node);
	if (objects_bvh_subdivide(root_node) < 0)
	{
		objects_bvh_free_tree(root_node);
		return (NULL);
	}
	return (root_node);
}

void	objects_bvh_free_tree(t_objects_bvh_node *root_node)
{
	if (root_node == NULL)
		return ;
	if (root_node->left_node != NULL)
		objects_bvh_free_tree(root_node->left_node);
	if (root_node->right_node != NULL)
		objects_bvh_free_tree(root_node->right_node);
	objects_bvh_free_node(root_node);
}
