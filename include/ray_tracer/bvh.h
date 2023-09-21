/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 21:49:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/14 21:49:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_HPP
# define BVH_HPP

# include "math/vector.h"
# include "vectors.h"
# include "object.h"
# include "scene.h"

typedef struct s_objects_bvh_node
{
	t_vector3f					aabb_min;
	t_vector3f					aabb_max;
	struct s_objects_bvh_node	*left_node;
	struct s_objects_bvh_node	*right_node;
	bool						is_leaf;
	t_vectors_int				index_objects;
	const t_objects				*objects;
	struct s_objects_bvh_node	*previous_node;
	size_t						nb_split_objects;
}	t_objects_bvh_node;

typedef struct s_mesh_bvh_node
{
	t_vector3f					aabb_min;
	t_vector3f					aabb_max;
	struct s_mesh_bvh_node		*left_node;
	struct s_mesh_bvh_node		*right_node;
	bool						is_leaf;
	t_vectors_int				index_faces;
	const t_object				*mesh_object;
	struct s_mesh_bvh_node		*previous_node;
	size_t						nb_split_triangles;
}	t_mesh_bvh_node;

typedef struct s_aabb_split
{
	t_axis	axis;
	float	middle;
}	t_aabb_split;

typedef enum e_bvh_side
{
	LEFT,
	RIGHT,
	LEFT_AND_RIGHT,
}	t_side;

//	mesh/bounding_box.c
t_aabb_split		split_bounding_box_mesh_node(t_mesh_bvh_node *node);
t_side				get_face_side(t_mesh_bvh_node *node, int face_index, t_aabb_split split);

//	mesh/node.c
t_mesh_bvh_node		*mesh_bvh_create_node(const t_object *mesh_object);
t_mesh_bvh_node		*mesh_bvh_create_root(const t_object *mesh_object);
void				mesh_bvh_free_node(t_mesh_bvh_node *node);
void				mesh_bvh_update_node_bounding_box(t_mesh_bvh_node *node);

//	mesh/subdivide.c
int					mesh_bvh_subdivide(t_mesh_bvh_node *node);

//	mesh/tree.c
t_mesh_bvh_node		*mesh_bvh_create_tree(const t_object *mesh_object);
void				mesh_bvh_free_tree(t_mesh_bvh_node *root_node);
void				mesh_bvh_update_tree(const t_object *mesh_object,
						t_mesh_bvh_node *tree);

//	objects/bounding_box.c
t_aabb_split		split_bounding_box_objects_node(t_objects_bvh_node *node);
t_side				get_bounding_box_side(t_bounding_box *bh,
						t_aabb_split split);

//	objects/node.c
t_objects_bvh_node	*objects_bvh_create_node(const t_objects *objects);
t_objects_bvh_node	*objects_bvh_create_root(const t_objects	*objects);
void				objects_bvh_free_node(t_objects_bvh_node *node);
void				objects_bvh_update_node_bounding_box(t_objects_bvh_node \
														*node);
//	objects/subdivide.c
int					objects_bvh_subdivide(t_objects_bvh_node *node);

//	objects/tree.c
t_objects_bvh_node	*objects_bvh_create_tree(const t_objects *objects);
void				objects_bvh_free_tree(t_objects_bvh_node *root_node);

//	recalculate_bvh.c
int					recalculate_bvh_scene(t_scene *scene, t_object *update_object);


#endif