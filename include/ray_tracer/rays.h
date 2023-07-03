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

typedef struct s_ray
{
	t_vector3f	origin;
	t_vector3f	direction;
}	t_ray;

typedef struct s_hit
{
	bool			hit;
	float			distance;
	const t_object	*object;
	t_vector3f		position;
	t_vector3f		normal;
	t_ray			ray;
	t_vector3f		albedo;
	float			t;
}	t_hit;

//	ray.c
t_ray		ray_create(t_vector3f origin, t_vector3f direction);
t_vector3f	ray_at(const t_ray *ray, float t);
t_vector3f	reflect(t_vector3f i, t_vector3f n);

float		calculate_object_distance(const t_ray *ray, const t_object *object);
t_hit		hit_object(const t_ray *ray, const t_object *object, float distance);
t_hit		calculate_ray_intersection(const t_ray *ray, const t_scene *scene);
t_hit		miss_hit(void);

t_hit	hit_sphere(const t_ray *ray, const t_object *sphere, float distance);
t_hit	hit_plane(const t_ray *ray, const t_object *plane, float distance);
t_hit	hit_infinite_cylinder(const t_ray *ray, const t_object *cylinder, float distance);
t_hit	hit_cylinder(const t_ray *ray, const t_object *cylinder, float distance);
float	calculate_cylinder_distance(const t_ray *ray, const t_object *cylinder);

t_vector3f	calculate_infinite_cylinder_normal(const t_ray *ray, const t_object *cylinder,
												 float distance);
float	calculate_sphere_distance(const t_ray *ray, const t_object *sphere);
float	calculate_plane_distance(const t_ray *ray, const t_object *plane);
float	calculate_inf_cylinder_distance(const t_ray *ray, const t_object *cylinder);
#endif
