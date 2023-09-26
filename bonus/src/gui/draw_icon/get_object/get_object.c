/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 00:43:07 by vfries            #+#    #+#             */
/*   Updated: 2023/09/24 01:18:45 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "engine.h"
#include "object.h"
#include "gui/utils.h"

static t_object		get_sphere(const t_camera *camera, t_material material);
static t_object		get_plane(t_material material);
static t_object		get_cylinder(const t_camera *camera, t_material material);
static t_object		get_cone(const t_camera *camera, t_material material);

t_object	get_object(const t_object *base_object, t_engine *tmp_engine)
{
	t_material	new_material;

	ft_bzero(&new_material, sizeof(new_material));
	if (material_deep_copy(&new_material, &base_object->material) < 0)
		ft_fatal_error("material_deep_copy() failed during draw_icon()");
	if (base_object->type == SPHERE)
		return (get_sphere(&tmp_engine->camera, new_material));
	else if (base_object->type == PLANE)
		return (get_plane(new_material));
	else if (base_object->type == CYLINDER)
		return (get_cylinder(&tmp_engine->camera, new_material));
	else if (base_object->type == CONE)
		return (get_cone(&tmp_engine->camera, new_material));
	else
		return (get_mesh_object(&tmp_engine->camera, base_object));
}

static t_object	get_sphere(const t_camera *camera, const t_material material)
{
	t_vector3f	top;
	t_vector3f	bottom;
	float		radius;

	if (camera->viewport.size.x >= camera->viewport.size.y)
	{
		top = get_ray_direction(camera, camera->viewport.size.y / 15.f, \
			camera->viewport.size.x / 2.f);
		bottom = get_ray_direction(camera, camera->viewport.size.y \
			- camera->viewport.size.y / 15.f, camera->viewport.size.x / 2.f);
	}
	else
	{
		top = get_ray_direction(camera, camera->viewport.size.x / 15.f, \
			camera->viewport.size.y / 2.f);
		bottom = get_ray_direction(camera, camera->viewport.size.x \
			- camera->viewport.size.x / 15.f, camera->viewport.size.y / 2.f);
	}
	top = vector3f_multiply(top, 2.f / top.z);
	bottom = vector3f_multiply(bottom, 2.f / bottom.z);
	radius = vector3f_length(vector3f_subtract(top, bottom)) / 2.f;
	return (sphere_create(vector3f_create(0, 0, -2.f), radius, material));
}

static t_object	get_plane(const t_material material)
{
	return (plane_create(vector3f_create(0, -1, 0), vector3f_create(0, 1, 0),
			material));
}

static t_object	get_cylinder(const t_camera *camera, const t_material material)
{
	t_vector3f	top;
	t_vector3f	bottom;
	t_vector3f	left;
	t_vector3f	right;
	t_object	cylinder;

	top = get_ray_direction(camera, camera->viewport.size.y / 7.5f, \
			camera->viewport.size.x / 2.f);
	bottom = get_ray_direction(camera, camera->viewport.size.y \
			- camera->viewport.size.y / 7.5f, camera->viewport.size.x / 2.f);
	top = vector3f_multiply(top, 2.f / top.z);
	bottom = vector3f_multiply(bottom, 2.f / bottom.z);
	left = get_ray_direction(camera, camera->viewport.size.x / 8.f, \
		camera->viewport.size.y / 2.f);
	right = get_ray_direction(camera, camera->viewport.size.x \
		- camera->viewport.size.x / 8.f, camera->viewport.size.y / 2.f);
	left = vector3f_multiply(left, 2.f / left.z);
	right = vector3f_multiply(right, 2.f / right.z);
	cylinder = cylinder_create(vector3f_create(0, 0, -2.f),
			vector3f_create(-35, 0, 90), (t_object_size){vector3f_length(\
			vector3f_subtract(top, bottom)) / 2.5f, vector3f_length(\
			vector3f_subtract(left, right))}, material);
	return (cylinder);
}

static t_object	get_cone(const t_camera *camera, const t_material material)
{
	t_vector3f	top;
	t_vector3f	bottom;
	float		height;
	t_vector3f	left;
	t_vector3f	right;

	top = get_ray_direction(camera, camera->viewport.size.y / 7.5f, \
			camera->viewport.size.x / 2.f);
	bottom = get_ray_direction(camera, camera->viewport.size.y \
			- camera->viewport.size.y / 7.5f, camera->viewport.size.x / 2.f);
	top = vector3f_multiply(top, 2.f / top.z);
	bottom = vector3f_multiply(bottom, 2.f / bottom.z);
	height = vector3f_length(vector3f_subtract(top, bottom));
	left = get_ray_direction(camera, camera->viewport.size.x / 3.5f, \
		camera->viewport.size.y / 2.f);
	right = get_ray_direction(camera, camera->viewport.size.x \
		- camera->viewport.size.x / 3.5f, camera->viewport.size.y / 2.f);
	left = vector3f_multiply(left, 2.f / left.z);
	right = vector3f_multiply(right, 2.f / right.z);
	return (cone_create(vector3f_create(0, 0, -2),
			vector3f_create(0, 1, 0), (t_object_size){
			vector3f_length(vector3f_subtract(left, right)) / 2.f, height},
		material));
}
