#include "parsing.h"
#include "ray_tracer_gui_api.h"

static int	init_object(t_object *mesh, char **scene_content_line);

#include <stdio.h>
int	parse_mesh_object(t_engine *engine, char **scene_content_line,
						t_rt_file_requirements *rt_file_requirements)
{
	t_vector3f	tmp;
	t_object	mesh;

	(void)rt_file_requirements;
	if (init_object(&mesh, scene_content_line) < 0)
		return (-1);
	if (get_position(scene_content_line[1], &tmp) < 0)
		return (error("Error\nFailed to get mesh position\n"));
	mesh_object_set_position(&mesh, tmp);
	if (get_rotation(scene_content_line[2], &tmp) < 0)
		return (error("Error\nFailed to get mesh rotation\n"));
	mesh_object_set_rotation(&mesh, tmp);
	if (get_vector3f(scene_content_line[3], &tmp) < 0)
		return (error("Error\nFailed to get mesh scale\n"));
	mesh_object_set_scale(&mesh, tmp);
//	mesh.mesh.tree = mesh_bvh_create_tree(&mesh);
	if (add_object(engine, mesh) < 0)
		return (free_object(&mesh), -1);
	engine->scene.objects.data[engine->scene.objects.length - 1].mesh.tree = mesh_bvh_create_tree(&engine->scene.objects.data[engine->scene.objects.length - 1]);
//	printf("dup2: %p\n", mesh.mesh.tree);
//	t_mesh_bvh_node *tree = mesh.mesh.tree;
////	printf("%p\n", object->mesh.tree);
//	printf("%zu\n", tree->left_node->mesh_object->cache.mesh.vertex.length);
//	printf("%zu\n", tree->right_node->mesh_object->cache.mesh.vertex.length);
//	printf("%d\n", tree->right_node->is_leaf);
//	printf("%d\n", tree->left_node->is_leaf);
	return (0);
}

static int	init_object(t_object *mesh, char **scene_content_line)
{
	char		*quoted_obj_file;
	size_t		quoted_obj_file_len;
	t_material	material;

	if (get_color(scene_content_line[4], &material.albedo) < 0)
		return (error("Error\nFailed to get mesh albedo\n"));
	material = material_create(vector3f_divide(material.albedo, 255.f), 0, 0);
	quoted_obj_file = scene_content_line[5];
	quoted_obj_file_len = ft_strlen(quoted_obj_file);
	if (quoted_obj_file_len <= 2)
		return (error("Error\nFailed to get mesh .obj file\n"));
	quoted_obj_file[quoted_obj_file_len - 1] = '\0';
	if (mesh_object_initialize(mesh, quoted_obj_file + 1, material) < 0)
	{
		quoted_obj_file[quoted_obj_file_len - 1] = '\"';
		return (error("Error\nFailed to init mesh object\n"));
	}
	quoted_obj_file[quoted_obj_file_len - 1] = '\"';
	return (0);
}
