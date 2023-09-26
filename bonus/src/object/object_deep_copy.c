/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_deep_copy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:29:12 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/23 22:29:13 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "object.h"

int		object_cache_deep_copy(union u_object_cache *dst,
			const union u_object_cache *src, const enum e_object_type type);
void	object_cache_free(union u_object_cache *cache,
			const enum e_object_type type);

int	object_deep_copy(t_object *dst, const t_object *src)
{
	free_object(dst);
	dst->type = src->type;
	dst->position = src->position;
	dst->radius = src->radius;
	dst->height = src->height;
	dst->axis = src->axis;
	dst->axis_degrees = src->axis_degrees;
	if (material_deep_copy(&dst->material, &src->material) < 0)
		return (-1);
	if (object_cache_deep_copy(&dst->cache, &src->cache, src->type) < 0)
		return (material_free(&dst->material), -1);
	dst->name = ft_strdup(src->name);
	if (dst->name == NULL)
		return (material_free(&dst->material),
			object_cache_free(&dst->cache, src->type), -1);
	if (mesh_deep_copy(&dst->mesh, &src->mesh) < 0)
		return (material_free(&dst->material),
			object_cache_free(&dst->cache, src->type), free(dst->name), -1);
	return (0);
}

int	object_cache_deep_copy(union u_object_cache *dst,
		const union u_object_cache *src, const enum e_object_type type)
{
	t_mesh_object_cache			*mesh_dst;
	const t_mesh_object_cache	*mesh_src = &src->mesh;

	if (type != MESH)
	{
		*dst = *src;
		return (0);
	}
	mesh_dst = &dst->mesh;
	if (vectors3f_deep_copy(&mesh_dst->vertex, &mesh_src->vertex) < 0)
		return (-1);
	if (vectors3f_deep_copy(&mesh_dst->normals, &mesh_src->normals) < 0)
		return (vectors3f_free(&mesh_dst->vertex), -1);
	mesh_dst->rotation = mesh_src->rotation;
	mesh_dst->translation = mesh_src->translation;
	mesh_dst->scale = mesh_src->scale;
	mesh_dst->scale_vector = mesh_src->scale_vector;
	return (0);
}

void	object_cache_free(union u_object_cache *cache,
		const enum e_object_type type)
{
	if (type != MESH)
		return ;
	vectors3f_free(&cache->mesh.vertex);
	vectors3f_free(&cache->mesh.normals);
}
