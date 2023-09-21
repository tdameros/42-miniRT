/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounding_box.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:29:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/13 12:29:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "render_frame.h"
#include "ray_tracer/bvh.h"
#include "draw.h"

static void	draw_objects_bvh_tree(t_engine *engine,
				t_objects_bvh_node *root_node,
				int color_level);
static void	draw_mesh_bvh_tree(t_engine *engine,
								  t_mesh_bvh_node *root_node,
								  int color_level);

void	render_bounding_box(t_engine *engine)
{
//	for (size_t i = 0; i < engine->scene.objects.length; i++)
//	{
//		t_object	*object = &engine->scene.objects.data[i];
//
//		object_calculate_bounding_box(object);
//		if (object->type == MESH)
//		{
//			object->mesh.tree = mesh_bvh_create_tree(object);
//			draw_mesh_bvh_tree(engine, object->mesh.tree, 0);
//		}
//	}
//	(void) engine;
//	(void)draw_mesh_bvh_tree;
//	(void) draw_objects_bvh_tree;
//	objects_bvh_free_tree(engine->scene.bvh_tree);
//	engine->scene.bvh_tree = objects_bvh_create_tree(&engine->scene.objects);
	change_image_color(&engine->bvh_image, COLOR_TRANSPARENT);
	(void) draw_mesh_bvh_tree;
	if (engine->display_bounding_box)
		draw_objects_bvh_tree(engine, engine->scene.bvh_tree, 0);
}

static void	draw_objects_bvh_tree(t_engine *engine,
								t_objects_bvh_node *root_node,
								int color_level)
{
	const t_vector3f	colors[6] = {
		(t_vector3f){255.f, 0.f, 0.f}, (t_vector3f){0.f, 255.f, 0.f},
		(t_vector3f){0.f, 0.f, 255.f}, (t_vector3f){0.f, 255.f, 255.f},
		(t_vector3f){255.f, 255.f, 0.f}, (t_vector3f){0.f, 255.f, 255.f}};

	if (root_node == NULL || color_level >= 6)
		return ;
	draw_objects_bvh_node(engine, root_node, colors[color_level]);
	if (root_node->is_leaf)
		return ;
	draw_objects_bvh_tree(engine, root_node->left_node, color_level + 1);
	draw_objects_bvh_tree(engine, root_node->right_node, color_level + 1);
}

static void	draw_mesh_bvh_tree(t_engine *engine,
		t_mesh_bvh_node *root_node, int color_level)
{
	const t_vector3f	colors[6] = {
		(t_vector3f){255.f, 0.f, 0.f}, (t_vector3f){0.f, 255.f, 0.f},
		(t_vector3f){0.f, 0.f, 255.f}, (t_vector3f){0.f, 255.f, 255.f},
		(t_vector3f){255.f, 255.f, 0.f}, (t_vector3f){0.f, 255.f, 255.f}};

	if (root_node == NULL || color_level >= 6)
		return ;
	draw_mesh_bvh_node(engine, root_node, colors[color_level]);
	if (root_node->is_leaf)
		return ;
	draw_mesh_bvh_tree(engine, root_node->left_node, color_level + 1);
	draw_mesh_bvh_tree(engine, root_node->right_node, color_level + 1);
}
