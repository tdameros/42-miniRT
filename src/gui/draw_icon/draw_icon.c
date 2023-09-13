/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_icon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 01:03:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/09 01:03:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "engine.h"
#include "ray_tracer/render.h"
#include "gui/utils.h"

static void			tmp_camera_create(t_camera *camera, t_vector2f viewport);
static void			init_tmp_scene(t_engine *tmp_engine, const t_object *object,
						t_vector3f sky_color);
static t_object		get_sphere(const t_camera *camera, t_material material);
static t_object		get_plane(t_material material);
static t_object		get_cylinder(const t_camera *camera, t_material material);
static t_object		get_cone(const t_camera *camera, t_material material);
static t_object		get_mesh_object(const t_camera *camera,
						const t_object *object);
static t_vector3f	get_mesh_object_scale(const t_object *mesh, float max_width,
						float max_height);

void	draw_icon(t_image *image, const t_object *object, const t_light *light,
			const unsigned int background_color)
{
	t_engine		tmp_engine;
	const t_color	sky_color = vector3f_divide(
			get_t_color_from_uint(background_color), 255.f);

	if (light != NULL)
		return (draw_light_icon(image, background_color, light->color));
	if (object == NULL)
		return ;
	ft_bzero(&tmp_engine, sizeof(tmp_engine));
	tmp_engine.ray_traced_image = *image;
	tmp_camera_create(&tmp_engine.camera,
		(t_vector2f){image->width, image->height});
	init_tmp_scene(&tmp_engine, object, sky_color);
	render_icon(&tmp_engine, background_color);
//	free(tmp_engine.camera.rays);
//	free_objects(&tmp_engine.scene.objects); // TODO causes use after free! (need to make deep copy of object)
	free_lights(&tmp_engine.scene.lights);
}

static void	tmp_camera_create(t_camera *camera, t_vector2f viewport)
{
	camera->viewport.number_of_pixels = viewport.x * viewport.y;
//	camera->rays = malloc(sizeof(*camera->rays)
//			* camera->viewport.number_of_pixels);
//	if (camera->rays == NULL)
//		return (-1);
	camera->viewport.size = viewport;
	camera->position = vector3f_create(0, 0, 0);
	camera->direction = vector3f_create(0, 0, -1);
	camera->up_vector = vector3f_create(0, 1, 0);
	camera->view = matrix4_create_identity();
	camera->inverse_view = matrix4_create_identity();
	camera->projection = matrix4_create_identity();
	camera->inverse_projection = matrix4_create_identity();
	camera->horizontal_fov = 45.f;
	camera->near_clip = 0.1f;
	camera->far_clip = 100;
	camera->pitch = 0;
	camera->rotation_speed = 0.3f;
	camera->lock = true;
	camera_recalculate_view(camera);
	camera_recalculate_projection(camera);
	// TODO exit on error
//	camera_recalculate_rays(camera);
}

static void	init_tmp_scene(t_engine *tmp_engine, const t_object *base_object,
				const t_vector3f sky_color)
{
	t_object	object;
	t_light		light;

	initialize_objects_array(&tmp_engine->scene.objects, 1);
	initialize_lights_array(&tmp_engine->scene.lights, 1);

	if (base_object->type == SPHERE)
		object = get_sphere(&tmp_engine->camera, base_object->material);
	else if (base_object->type == PLANE)
		object = get_plane(base_object->material);
	else if (base_object->type == CYLINDER)
		object = get_cylinder(&tmp_engine->camera, base_object->material);
	else if (base_object->type == CONE)
		object = get_cone(&tmp_engine->camera, base_object->material);
	else
		object = get_mesh_object(&tmp_engine->camera, base_object);
	add_object_in_objects(&tmp_engine->scene.objects, object);
	// TODO exit on error

	light = light_create(vector3f_create(5, 5, 5), vector3f_create(1, 1, 1),
			1.f);
	add_light_in_lights(&tmp_engine->scene.lights, light);
	// TODO exit on error

	tmp_engine->scene.sky_color = sky_color;
	tmp_engine->scene.ambient_light.color = vector3f_create(1, 1, 1);
	tmp_engine->scene.ambient_light.brightness = 0.2f;
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
	float		radius;
	t_vector3f	left;
	t_vector3f	right;
	float		height;
	t_object	cylinder;

	top = get_ray_direction(camera, camera->viewport.size.y / 7.5f, \
			camera->viewport.size.x / 2.f);
	bottom = get_ray_direction(camera, camera->viewport.size.y \
			- camera->viewport.size.y / 7.5f, camera->viewport.size.x / 2.f);
	top = vector3f_multiply(top, 2.f / top.z);
	bottom = vector3f_multiply(bottom, 2.f / bottom.z);
	radius = vector3f_length(vector3f_subtract(top, bottom)) / 2.5f;
	left = get_ray_direction(camera, camera->viewport.size.x / 8.f, \
		camera->viewport.size.y / 2.f);
	right = get_ray_direction(camera, camera->viewport.size.x \
		- camera->viewport.size.x / 8.f, camera->viewport.size.y / 2.f);
	left = vector3f_multiply(left, 2.f / left.z);
	right = vector3f_multiply(right, 2.f / right.z);
	height = vector3f_length(vector3f_subtract(left, right));
	cylinder = cylinder_create(vector3f_create(0, 0, -2.f),
			vector3f_create(1, 0, 0), (t_object_size){radius, height},
			material);
	object_rotate(&cylinder, (t_vector3f){0.f, 1.f, 0.f}, -35);
	return (cylinder);
}

static t_object	get_cone(const t_camera *camera, const t_material material)
{
	t_vector3f	top;
	t_vector3f	bottom;
	float		height;
	t_vector3f	left;
	t_vector3f	right;
	float		radius;

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
	radius = vector3f_length(vector3f_subtract(left, right)) / 2.f;
	return (cone_create(vector3f_create(0, 0, -2),
			vector3f_create(0, 1, 0), (t_object_size){radius, height}, \
			material));
}

static t_object	get_mesh_object(const t_camera *camera, const t_object *object)
{
	t_vector3f	top;
	t_vector3f	bottom;
	t_vector3f	left;
	t_vector3f	right;
	t_object	mesh_object;
	float		min_y;

	top = get_ray_direction(camera, camera->viewport.size.y / 7.5f, \
			camera->viewport.size.x / 2.f);
	bottom = get_ray_direction(camera, camera->viewport.size.y \
			- camera->viewport.size.y / 7.5f, camera->viewport.size.x / 2.f);
	top = vector3f_multiply(top, 2.f / top.z);
	bottom = vector3f_multiply(bottom, 2.f / bottom.z);
	left = get_ray_direction(camera, camera->viewport.size.x / 3.5f, \
		camera->viewport.size.y / 2.f);
	right = get_ray_direction(camera, camera->viewport.size.x \
		- camera->viewport.size.x / 3.5f, camera->viewport.size.y / 2.f);
	left = vector3f_multiply(left, 2.f / left.z);
	right = vector3f_multiply(right, 2.f / right.z);
	ft_bzero(&mesh_object, sizeof(mesh_object));
	object_deep_copy(&mesh_object, object); // TODO secure me
	mesh_object_set_position(&mesh_object, vector3f_create(0, 0, -2.f));
	mesh_object_set_rotation(&mesh_object, vector3f_create(0, 30, 0));
	mesh_object_set_scale(&mesh_object, get_mesh_object_scale(&mesh_object,
			vector3f_length(vector3f_subtract(left, right)),
			vector3f_length(vector3f_subtract(bottom, top))));
	min_y = vectors3f_get_min_values(mesh_object.cache.mesh.vertex).y;
	mesh_object_set_position(&mesh_object, vector3f_create(0, bottom.y - min_y, -2.f));
//	mesh_object_set_scale(&mesh_object, (t_vector3f){1, 1, 1});
	return (mesh_object);
}

static t_vector3f	get_mesh_object_scale(const t_object *mesh, float max_width,
						float max_height)
{
	const float	width = mesh->mesh.vertex_max.x - mesh->mesh.vertex_min.x;
	const float	height = mesh->mesh.vertex_max.y - mesh->mesh.vertex_min.y;
	const float	scale = fminf(max_width / width, max_height / height);

	return ((t_vector3f){scale, scale, scale});
}
