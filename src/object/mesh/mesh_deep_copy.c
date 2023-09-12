#include "object.h"

int	mesh_deep_copy(t_mesh *dst, const t_mesh *src)
{
	mesh_free(dst);
	if (vectors3f_deep_copy(&dst->base_vertex, &src->base_vertex) < 0)
		return (-1);
	dst->vertex_min = src->vertex_min;
	dst->vertex_max = src->vertex_max;
	if (vectors3f_deep_copy(&dst->base_normals, &src->base_normals) < 0)
		return (vectors3f_free(&dst->base_vertex), -1);
	if (mesh_faces_deep_copy(&dst->faces, &src->faces) < 0)
		return (vectors3f_free(&dst->base_vertex),
			vectors3f_free(&dst->base_normals), -1);
	return (0);
}
