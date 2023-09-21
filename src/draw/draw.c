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
	(void) draw_mesh_bvh_tree;
	change_image_color(&engine->bvh_image, COLOR_TRANSPARENT);
	if (engine->gui.selected_object.object != NULL
		&& engine->gui.selected_object.object->type != PLANE)
		draw_bounding_box(engine,
			&engine->gui.selected_object.object->bounding_box,
			(t_vector3f){255.f, 255.f, 255.f});
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
