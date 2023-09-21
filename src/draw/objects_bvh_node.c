/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_bvh_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:27:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/17 15:27:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void			draw_objects_bvh_objects_node(t_engine *engine,
						t_objects_bvh_node *node,
						t_vector3f color);
static void			draw_bounding_box(t_engine *engine,
						t_bounding_box *bounding_box,
						t_vector3f color);
static t_vector2i	convert_world_point_to_screen_space(t_camera *camera,
						t_vector3f world_point);
static void			draw_bounding_box_points(t_engine *engine,
						t_vector2i points[8], t_vector3f color);

void	draw_objects_bvh_node(t_engine *engine, t_objects_bvh_node *node,
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
		draw_objects_bvh_objects_node(engine, node,
			(t_vector3f){255.f, 255.f, 255.f});
}

static void	draw_objects_bvh_objects_node(t_engine *engine,
										t_objects_bvh_node *node,
										t_vector3f color)
{
	size_t		i;
	t_object	*object;


	i = 0;
	while (i < node->index_objects.length)
	{
		object = &node->objects->data[node->index_objects.data[i]];
		if (object->type != PLANE)
			draw_bounding_box(engine, &object->bounding_box, color);
		i++;
	}
}

static	void	draw_bounding_box(t_engine *engine,
									t_bounding_box *bounding_box,
									t_vector3f color)
{
	t_vector2i	points[8];

	points[0] = convert_world_point_to_screen_space(&engine->camera,
			bounding_box->top_face[0]);
	points[1] = convert_world_point_to_screen_space(&engine->camera,
			bounding_box->top_face[1]);
	points[2] = convert_world_point_to_screen_space(&engine->camera,
			bounding_box->top_face[2]);
	points[3] = convert_world_point_to_screen_space(&engine->camera,
			bounding_box->top_face[3]);
	points[4] = convert_world_point_to_screen_space(&engine->camera,
			bounding_box->bottom_face[0]);
	points[5] = convert_world_point_to_screen_space(&engine->camera,
			bounding_box->bottom_face[1]);
	points[6] = convert_world_point_to_screen_space(&engine->camera,
			bounding_box->bottom_face[2]);
	points[7] = convert_world_point_to_screen_space(&engine->camera,
			bounding_box->bottom_face[3]);
	draw_bounding_box_points(engine, points, color);
}

static	t_vector2i	convert_world_point_to_screen_space(t_camera *camera,
														t_vector3f world_point)
{
	const t_vector4f	world = (t_vector4f){world_point.x, \
											world_point.y, \
											world_point.z, 1};
	t_vector4f			screen_space;
	t_vector2f			screen_position;

	screen_space = matrix4_multiply_vector4(&camera->view, world);
	screen_space = matrix4_multiply_vector4(&camera->projection, screen_space);
	if (screen_space.w < camera->near_clip)
		return ((t_vector2i){-1, -1});
	screen_space = vector4f_divide(screen_space, screen_space.w);
	screen_position = (t_vector2f){screen_space.x, screen_space.y};
	screen_position = vector2f_divide(vector2f_add(screen_position,
				(t_vector2f){1.f, 1.f}), 2);
	screen_position.y = 1.f - screen_position.y;
	screen_position.y = screen_position.y * camera->viewport.size.y;
	screen_position.x = screen_position.x * camera->viewport.size.x;
	return ((t_vector2i){(int) screen_position.x, (int) screen_position.y});
}

static void	draw_bounding_box_points(t_engine *engine, t_vector2i points[8],
										t_vector3f color)
{
	draw_line(&engine->bvh_image, points[0], points[1], color);
	draw_line(&engine->bvh_image, points[1], points[2], color);
	draw_line(&engine->bvh_image, points[2], points[3], color);
	draw_line(&engine->bvh_image, points[3], points[0], color);

	draw_line(&engine->bvh_image, points[4], points[5], color);
	draw_line(&engine->bvh_image, points[5], points[6], color);
	draw_line(&engine->bvh_image, points[6], points[7], color);
	draw_line(&engine->bvh_image, points[7], points[4], color);

	draw_line(&engine->bvh_image, points[0], points[4], color);
	draw_line(&engine->bvh_image, points[1], points[5], color);
	draw_line(&engine->bvh_image, points[2], points[6], color);
	draw_line(&engine->bvh_image, points[3], points[7], color);
}
