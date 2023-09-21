/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subdivide.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:26:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/15 17:26:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer/bvh.h"

static int			fill_children_nodes(t_objects_bvh_node *node);
static int			add_obj_index_in_child_node(t_objects_bvh_node *node,
						size_t obj_index, t_side side);
static bool			is_duplicated_node(t_objects_bvh_node *node);
static void			remove_duplicated_node(t_objects_bvh_node *node);

int	objects_bvh_subdivide(t_objects_bvh_node *node)
{
	if (node == NULL)
		return (0);
	if (node->index_objects.length <= 2)
	{
		node->is_leaf = true;
		return (0);
	}
	if (fill_children_nodes(node) < 0)
		return (-1);
	node->left_node->previous_node = node;
	node->right_node->previous_node = node;
	node->nb_split_objects = node->index_objects.length;
	if (is_duplicated_node(node))
	{
		remove_duplicated_node(node);
		return (0);
	}
	vectors_int_free(&node->index_objects);
	objects_bvh_update_node_bounding_box(node->left_node);
	objects_bvh_update_node_bounding_box(node->right_node);
	if (objects_bvh_subdivide(node->left_node) < 0)
		return (-1);
	if (objects_bvh_subdivide(node->right_node) < 0)
		return (-1);
	return (0);
}

static int	fill_children_nodes(t_objects_bvh_node *node)
{
	const t_aabb_split		split = split_bounding_box_objects_node(node);
	t_bounding_box			*bounding_box;
	t_side					side;
	size_t					i;
	size_t					obj_index;

	node->left_node = objects_bvh_create_node(node->objects);
	node->right_node = objects_bvh_create_node(node->objects);
	if (node->left_node == NULL || node->right_node == NULL)
		return (-1);
	i = 0;
	while (i < node->index_objects.length)
	{
		obj_index = node->index_objects.data[i];
		bounding_box = &node->objects->data[obj_index].bounding_box;
		side = get_bounding_box_side(bounding_box, split);
		if (add_obj_index_in_child_node(node, obj_index, side) < 0)
			return (-1);
		i++;
	}
	return (0);
}

static int	add_obj_index_in_child_node(t_objects_bvh_node *node,
										size_t obj_index, t_side side)
{
	if (side == LEFT_AND_RIGHT || side == LEFT)
	{
		if (vectors_int_add(&node->left_node->index_objects, obj_index) < 0)
			return (-1);
	}
	if (side == LEFT_AND_RIGHT || side == RIGHT)
	{
		if (vectors_int_add(&node->right_node->index_objects, obj_index) < 0)
			return (-1);
	}
	return (0);
}

static bool	is_duplicated_node(t_objects_bvh_node *node)
{
	return (node->previous_node != NULL \
	&& (node->left_node->index_objects.length \
		== node->previous_node->nb_split_objects \
		|| node->right_node->index_objects.length \
		== node->previous_node->nb_split_objects));
}

static void	remove_duplicated_node(t_objects_bvh_node *node)
{
	objects_bvh_free_node(node->left_node);
	objects_bvh_free_node(node->right_node);
	node->previous_node->left_node = NULL;
	node->previous_node->right_node = NULL;
	node->previous_node->is_leaf = true;
	node->previous_node->index_objects = node->index_objects;
	node->index_objects.data = NULL;
	objects_bvh_free_node(node);
}
