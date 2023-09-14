#include "libft.h"

#include "object.h"

void	mesh_object_update_vertex(t_object *mesh_object)
{
	size_t		i;
	t_matrix4	global_matrix;

	if (mesh_object->type != MESH)
		return ;
	global_matrix = matrix4_multiply(&mesh_object->cache.mesh.scale,
			&mesh_object->cache.mesh.rotation);
	global_matrix = matrix4_multiply(&global_matrix,
			&mesh_object->cache.mesh.translation);
	i = mesh_object->cache.mesh.vertex.length;
	while (i--)
		mesh_object->cache.mesh.vertex.data[i] = matrix4_multiply_vector3(
				&global_matrix, mesh_object->mesh.base_vertex.data[i]);
}

void	mesh_object_update_normals(t_object *mesh_object)
{
	size_t	i;

	if (mesh_object->type != MESH)
		return ;
	i = mesh_object->cache.mesh.normals.length;
	while (i--)
		mesh_object->cache.mesh.normals.data[i] = matrix4_multiply_vector3(
				&mesh_object->cache.mesh.rotation,
				mesh_object->mesh.base_normals.data[i]);
}

void	mesh_cache_free(t_mesh_object_cache *cache)
{
	vectors3f_free(&cache->vertex);
	vectors3f_free(&cache->normals);
	free(cache->obj_file_path);
	ft_bzero(cache, sizeof(*cache));
}
