/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:54:37 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/06 17:54:41 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYS_H
# define RAYS_H

# include <stdbool.h>
# include <stddef.h>

# include "math/vector.h"
# include "scene.h"
# include "object.h"
# include "camera.h"
# include "ray_tracer/bvh.h"

# define HIT_DISPLACEMENT 0.01f

typedef struct s_recalculate_rays_args
{
	struct s_camera	*camera;
	int				current_line;
}	t_recalculate_rays_args;

typedef struct s_ray
{
	t_vector3f	origin;
	t_vector3f	direction;
}	t_ray;

enum e_hit_context
{
	OUTLINE,
	CAP1,
	CAP2,
};

typedef struct s_hit
{
	bool				hit;
	float				distance;
	const t_object		*object;
	t_vector3f			position;
	t_vector3f			normal;
	t_vector3f			shade_normal;
	t_ray				ray;
	t_vector3f			albedo;
	ssize_t				index_obj;
	enum e_hit_context	context;
}	t_hit;

t_hit	calculate_shadow_ray_intersection(const t_ray *ray,
										   const float light_distance,
										   const t_scene *scene);

//	intersections/aabb.c
bool		ray_intersect_aabb(const t_ray *ray, const t_vector3f aabb_min,
				const t_vector3f aabb_max, float near_distance);

//	intersections/cone.c
t_hit		hit_cone(const t_ray *ray, const t_object *cone,
				const t_hit hit_distance);
t_hit		calculate_cone_distance(const t_ray *ray, const t_object *cone);

//	intersections/cone_utils.c
bool		is_in_outline_cone(const t_ray *ray, const t_object *cone,
				const float distance);
float		calculate_outline_cone_distance(const t_ray *ray,
				const t_object *cone);
t_vector3f	calculate_outline_cone_normal(const t_ray *ray,
				const t_object *cone,
				const float distance);
float		calculate_cap_cone_distance(const t_ray *ray, const t_object *cone);

//	intersections/cylinder.c
t_hit		hit_cylinder(const t_ray *ray, const t_object *cylinder,
				const t_hit hit_distance);
t_hit		calculate_cylinder_distance(const t_ray *ray,
				const t_object *cylinder);

//	intersections/cylinder_caps.c
t_hit		calculate_cylinder_caps_distance(const t_ray *ray,
				const t_object *cylinder);

//	intersections/cylinder_infinite.c
t_hit		hit_infinite_cylinder(const t_ray *ray, const t_object *cylinder,
				const t_hit hit_distance);
t_vector3f	calculate_infinite_cylinder_normal(const t_ray *ray,
				const t_object *cylinder, const float distance);
t_hit		calculate_inf_cylinder_distance(const t_ray *ray,
				const t_object *cylinder);

//	intersections/intersection.c
t_hit		calculate_ray_intersection(const t_ray *ray, const t_scene *scene);
t_hit		calculate_object_distance(const t_ray *ray, const t_object *object);
t_hit		miss_hit(void);
t_hit		hit_object(const t_ray *ray, const t_object *object,
				t_hit hit_distance);

//	intersections/mesh.c
t_hit		calculate_mesh_distance(const t_ray *ray, const t_object *mesh);
t_hit		hit_mesh(const t_ray *ray, const t_object *mesh,
					  const t_hit hit_distance);

//	intersections/objects_bvh.c
t_hit		mesh_bvh_calculate_ray_intersection(const t_ray *ray, const t_mesh_bvh_node *tree);


//	intersections/objects_bvh.c
t_hit		objects_bvh_calculate_ray_intersection(const t_ray *ray,
													const t_objects_bvh_node *tree);

//	intersections/plane.c
t_hit		hit_plane(const t_ray *ray, const t_object *plane,
				const t_hit hit_distance);
t_hit		calculate_plane_distance(const t_ray *ray, const t_object *plane);

//	intersections/sphere.c
t_hit		hit_sphere(const t_ray *ray, const t_object *sphere,
				const t_hit hit_distance);
t_hit		calculate_sphere_distance(const t_ray *ray, const t_object *sphere);

//	context.c
bool		is_cap_context(enum e_hit_context context);
bool		context_has_normal_map(enum e_hit_context context,
				const t_material *material);

//	hit.c
t_hit		min_hit(t_hit hit, t_hit near_hit);

//	ray.c
t_ray		ray_create(const t_vector3f origin, const t_vector3f direction);
t_vector3f	ray_at(const t_ray *ray, const float t);
t_vector3f	reflect(const t_vector3f i, const t_vector3f n);

#endif
