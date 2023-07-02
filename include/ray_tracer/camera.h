/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:52:04 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/06 17:52:05 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "math/vector.h"
# include "math/matrix.h"
# include "ray_tracer/rays.h"

typedef struct s_viewport
{
	t_vector2f	size;
	size_t		number_of_pixels;
}	t_viewport;

typedef struct s_camera {

	t_vector3f	position;
	t_vector3f	direction;

	t_matrix4	view;
	t_matrix4	inverse_view;
	t_matrix4	projection;
	t_matrix4	inverse_projection;

	t_viewport	viewport;
	float		vertical_fov;
	float		near_clip;
	float		far_clip;

	float		pitch;
	float		rotation_speed;

	bool		lock;

	t_ray		*rays;
}	t_camera;

//	create.c
int			camera_create(t_camera *camera, t_vector2f viewport);

//	movement.c
void		camera_move_forward(t_camera *camera, float distance);
void		camera_move_left(t_camera *camera, float distance);
void		camera_rotate_left(t_camera *camera, float degrees);
void		camera_rotate_up(t_camera *camera, float degrees);

//	projection.c
void		camera_recalculate_projection(t_camera *camera);

//	ray.c
void		camera_recalculate_rays(t_camera *camera);

//	view.c
void		camera_recalculate_view(t_camera *camera);

#endif
