/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mesh_object.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 01:06:38 by vfries            #+#    #+#             */
/*   Updated: 2023/09/24 01:17:24 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "engine.h"

static void			init_top_and_bottom(const t_camera *camera, t_vector3f *top,
						t_vector3f *bottom);
static void			init_left_and_right(const t_camera *camera,
						t_vector3f *left, t_vector3f *right);
static t_vector3f	get_mesh_object_scale(const t_object *mesh, float max_width,
						float max_height);

t_object	get_mesh_object(const t_camera *camera, const t_object *object)
{
	t_vector3f	top;
	t_vector3f	bottom;
	t_vector3f	left;
	t_vector3f	right;
	t_object	mesh_object;

	init_top_and_bottom(camera, &top, &bottom);
	init_left_and_right(camera, &left, &right);
	ft_bzero(&mesh_object, sizeof(mesh_object));
	if (object_deep_copy(&mesh_object, object) < 0)
		ft_fatal_error("Failed to make a deep copy of mesh object");
	mesh_object_set_position(&mesh_object, vector3f_create(0, 0, -2.f));
	mesh_object_set_rotation(&mesh_object, vector3f_create(0, 30, 0));
	mesh_object_set_scale(&mesh_object, get_mesh_object_scale(&mesh_object,
			vector3f_length(vector3f_subtract(left, right)),
			vector3f_length(vector3f_subtract(bottom, top))));
	mesh_object_set_position(&mesh_object, vector3f_create(0, \
		bottom.y - vectors3f_get_min_values(mesh_object.cache.mesh.vertex).y, \
		-2.f));
	return (mesh_object);
}

static void	init_top_and_bottom(const t_camera *camera, t_vector3f *top,
				t_vector3f *bottom)
{
	*top = get_ray_direction(camera, camera->viewport.size.y / 7.5f, \
			camera->viewport.size.x / 2.f);
	*bottom = get_ray_direction(camera, camera->viewport.size.y \
			- camera->viewport.size.y / 7.5f, camera->viewport.size.x / 2.f);
	*top = vector3f_multiply(*top, 2.f / top->z);
	*bottom = vector3f_multiply(*bottom, 2.f / bottom->z);
}

static void	init_left_and_right(const t_camera *camera, t_vector3f *left,
				t_vector3f *right)
{
	*left = get_ray_direction(camera, camera->viewport.size.x / 3.5f, \
		camera->viewport.size.y / 2.f);
	*right = get_ray_direction(camera, camera->viewport.size.x \
		- camera->viewport.size.x / 3.5f, camera->viewport.size.y / 2.f);
	*left = vector3f_multiply(*left, 2.f / left->z);
	*right = vector3f_multiply(*right, 2.f / right->z);
}

static t_vector3f	get_mesh_object_scale(const t_object *mesh, float max_width,
						float max_height)
{
	const float	width = mesh->mesh.vertex_max.x - mesh->mesh.vertex_min.x;
	const float	height = mesh->mesh.vertex_max.y - mesh->mesh.vertex_min.y;
	const float	scale = fminf(max_width / width, max_height / height);

	return ((t_vector3f){scale, scale, scale});
}
