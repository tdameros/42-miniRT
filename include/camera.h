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

# include "vector.h"
# include "matrix.h"
# include "ray.h"

typedef struct s_camera {

	t_vector3	position;
	t_vector3	direction;

	t_matrix4	view;
	t_matrix4	inverse_view;
	t_matrix4	projection;
	t_matrix4	inverse_projection;

	t_vector2	viewport;
	double		vertical_fov;
	double		near_clip;
	double		far_clip;

	t_ray		*rays;
}	t_camera;

//	create.c
int			camera_create(t_camera *camera, t_vector2 viewport);

//	movement.c
void		camera_move_forward(t_camera *camera, double distance);
void		camera_move_left(t_camera *camera, double distance);
void		camera_rotate_left(t_camera *camera, double degrees);
void		camera_rotate_up(t_camera *camera, double degrees);

//	projection.c
void		camera_recalculate_projection(t_camera *camera);

//	ray.c
void		camera_recalculate_rays(t_camera *camera);

//	view.c
void		camera_recalculate_view(t_camera *camera);

#endif
