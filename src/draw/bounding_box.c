/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounding_box.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:22:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/21 16:22:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	draw_bounding_box_points(t_engine *engine, t_vector2i points[8],
				t_vector3f color);

void	draw_bounding_box(t_engine *engine, t_bounding_box *bounding_box,
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

t_vector2i	convert_world_point_to_screen_space(t_camera *camera,
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
