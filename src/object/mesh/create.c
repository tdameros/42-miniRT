/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:34:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/08/08 18:34:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "float.h"

#include "libft.h"

#include "object.h"
#include "vectors.h"
#include "ray_tracer/bvh.h"

static char	*get_obj_name(const char *obj_file);
static int	init_cache(t_object *mesh_object, const char *obj_file);

/*
 * Return code:
 * 1 mesh object has been successful initialize
 * 0 obj_file is empty
 * -1 an error has been encountered
 */
int	mesh_object_initialize(t_object *mesh_object, const char *obj_file,
				t_material material)
{
	int	return_code;

	ft_bzero(mesh_object, sizeof(*mesh_object));
	mesh_object->type = MESH;
	mesh_object->material = material;
	return_code = initialize_mesh_with_obj(&mesh_object->mesh, obj_file);
	if (return_code < 0)
		return (return_code);
	mesh_object->name = get_obj_name(obj_file);
	if (mesh_object->name == NULL)
	{
		mesh_free(&mesh_object->mesh);
		return (-1);
	}
	if (init_cache(mesh_object, obj_file) < 0)
	{
		mesh_free(&mesh_object->mesh);
		return (-1);
	}
	mesh_calculate_bounding_box(mesh_object);
	return (0);
}

static char	*get_obj_name(const char *obj_file)
{
	char	*obj_file_without_full_path;
	char	*obj_name;

	obj_file_without_full_path = ft_strrchr(obj_file, '/');
	if (obj_file_without_full_path != NULL)
	{
		obj_file_without_full_path++;
		obj_name = ft_substr(obj_file_without_full_path, 0,
				ft_strlen(obj_file_without_full_path) - 4);
	}
	else
		obj_name = ft_substr(obj_file, 0, ft_strlen(obj_file) - 4);
	if (obj_name != NULL)
		obj_name[0] = ft_toupper(obj_name[0]);
	return (obj_name);
}

void	mesh_free(t_mesh *mesh)
{
	mesh_bvh_free_tree(mesh->tree);
	vectors3f_free(&mesh->base_vertex);
	vectors3f_free(&mesh->base_normals);
	mesh_faces_free(&mesh->faces);
	ft_bzero(mesh, sizeof(*mesh));
}

static int	init_cache(t_object *mesh_object, const char *obj_file)
{
	t_mesh_object_cache	*cache;

	cache = &mesh_object->cache.mesh;
	cache->obj_file_path = ft_strdup(obj_file);
	if (cache->obj_file_path == NULL)
		return (-1);
	if (vectors3f_deep_copy(&cache->vertex, &mesh_object->mesh.base_vertex) < 0)
		return (mesh_cache_free(cache), -1);
	if (vectors3f_deep_copy(&cache->normals,
			&mesh_object->mesh.base_normals) < 0)
		return (mesh_cache_free(cache), -1);
	cache->translation = create_translation_matrix(mesh_object->position);
	cache->scale_vector = (t_vector3f){1, 1, 1};
	cache->scale = create_scale_matrix(cache->scale_vector);
	mesh_object->axis = (t_vector3f){0, 0, 0};
	mesh_object->axis_degrees = mesh_object->axis;
	cache->rotation = create_rotation_matrix(mesh_object->axis);
	mesh_object_update_normals(mesh_object);
	mesh_object_update_vertex(mesh_object);
	return (0);
}
