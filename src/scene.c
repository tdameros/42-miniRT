
#include "scene.h"
#include "ray_tracer/bvh.h"

void	free_scene(t_scene *scene)
{
	free_objects(&scene->objects);
	free_lights(&scene->lights);
	free_light(&scene->ambient_light);
	objects_bvh_free_tree(scene->bvh_tree);
	vectors_int_free(&scene->plane_indexes);
	ft_bzero(scene, sizeof(*scene));
}