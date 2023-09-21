/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:27:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/18 16:27:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "engine.h"

//	bounding_box.c
void		draw_bounding_box(t_engine *engine, t_bounding_box *bounding_box,
				t_vector3f color);
t_vector2i	convert_world_point_to_screen_space(t_camera *camera,
				t_vector3f world_point);

//	draw.c
void		render_bounding_box(t_engine *engine);

//	draw_line.c
void		draw_line(t_image *image, t_vector2i point1, t_vector2i point2,
				t_vector3f color);

//	objects_bvh_node.c
void		draw_objects_bvh_node(t_engine *engine, t_objects_bvh_node *node,
				t_vector3f color);

//	mesh_bvh_node.c
void		draw_mesh_bvh_node(t_engine *engine, t_mesh_bvh_node *node,
				t_vector3f color);

#endif