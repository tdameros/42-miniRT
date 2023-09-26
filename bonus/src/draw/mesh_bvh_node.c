/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_bvh_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:34:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/19 22:34:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	draw_mesh_bvh_faces_node(t_engine *engine,
				const t_mesh_bvh_node *node, t_vector3f color);

void	draw_mesh_bvh_node(t_engine *engine, const t_mesh_bvh_node *node,
				t_vector3f color)
{
	const t_vector3f	max = node->aabb_max;
	const t_vector3f	min = node->aabb_min;
	t_bounding_box		bounding_box;

	bounding_box.top_face[0] = (t_vector3f){max.x, max.y, min.z};
	bounding_box.top_face[1] = max;
	bounding_box.top_face[2] = (t_vector3f){min.x, max.y, max.z};
	bounding_box.top_face[3] = (t_vector3f){min.x, max.y, min.z};
	bounding_box.bottom_face[0] = (t_vector3f){max.x, min.y, min.z};
	bounding_box.bottom_face[1] = (t_vector3f){max.x, min.y, max.z};
	bounding_box.bottom_face[2] = (t_vector3f){min.x, min.y, max.z};
	bounding_box.bottom_face[3] = min;
	draw_bounding_box(engine, &bounding_box, color);
	if (node->is_leaf)
		draw_mesh_bvh_faces_node(engine, node,
			(t_vector3f){255.f, 255.f, 255.f});
}

static void	draw_mesh_bvh_faces_node(t_engine *engine,
									const t_mesh_bvh_node *node,
									t_vector3f color)
{
	t_vector3f	vertices[3];
	t_vector2i	points[3];
	size_t		i;

	i = 0;
	while (i < node->index_faces.length)
	{
		vertices[0] = mesh_get_vertex_from_face(node->mesh_object,
				node->index_faces.data[i], VERTEX_A);
		vertices[1] = mesh_get_vertex_from_face(node->mesh_object,
				node->index_faces.data[i], VERTEX_B);
		vertices[2] = mesh_get_vertex_from_face(node->mesh_object,
				node->index_faces.data[i], VERTEX_C);
		points[0] = convert_world_point_to_screen_space(&engine->camera,
				vertices[0]);
		points[1] = convert_world_point_to_screen_space(&engine->camera,
				vertices[1]);
		points[2] = convert_world_point_to_screen_space(&engine->camera,
				vertices[2]);
		draw_line(&engine->bvh_image, points[0], points[1], color);
		draw_line(&engine->bvh_image, points[1], points[2], color);
		draw_line(&engine->bvh_image, points[2], points[0], color);
		i++;
	}
}
