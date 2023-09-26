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

t_objects_bvh_node	*objects_bvh_create_node(const t_objects *objects)
{
	t_objects_bvh_node	*node;

	node = malloc(sizeof(*node));
	if (node == NULL)
		return (NULL);
	ft_bzero(node, sizeof(*node));
	node->objects = objects;
	if (vectors_int_initialize(&node->index_objects, 10) < 0)
	{
		free(node);
		return (NULL);
	}
	return (node);
}

t_objects_bvh_node	*objects_bvh_create_root(const t_objects	*objects)
{
	t_objects_bvh_node	*root_node;
	int					return_code;
	size_t				i;

	root_node = objects_bvh_create_node(objects);
	if (root_node == NULL)
		return (NULL);
	return_code = 0;
	i = 0;
	while (i < objects->length)
	{
		if (objects->data[i].type != PLANE)
			return_code = vectors_int_add(&root_node->index_objects, (int)i);
		if (return_code < 0)
		{
			objects_bvh_free_node(root_node);
			return (NULL);
		}
		i++;
	}
	root_node->nb_split_objects = objects->length;
	objects_bvh_update_node_bounding_box(root_node);
	return (root_node);
}

void	objects_bvh_free_node(t_objects_bvh_node *node)
{
	vectors_int_free(&node->index_objects);
	free(node);
}

void	objects_bvh_update_node_bounding_box(t_objects_bvh_node *node)
{
	t_vector3f	min;
	t_vector3f	max;
	t_object	object;
	size_t		i;

	min = (t_vector3f){FLT_MAX, FLT_MAX, FLT_MAX};
	max = (t_vector3f){-FLT_MAX, -FLT_MAX, -FLT_MAX};
	i = 0;
	while (i < node->index_objects.length)
	{
		object = node->objects->data[node->index_objects.data[i]];
		if (object.type != PLANE)
		{
			min = vector3f_min(min, object.bounding_box.aabb_min);
			max = vector3f_max(max, object.bounding_box.aabb_max);
		}
		i++;
	}
	node->aabb_min = min;
	node->aabb_max = max;
}
