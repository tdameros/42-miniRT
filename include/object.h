/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_object.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:42:20 by vfries            #+#    #+#             */
/*   Updated: 2023/05/07 18:42:20 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include <stddef.h>

#include "math/vector.h"
#include "colors.h"
#include "ray_tracer/ray.h"

enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
};

typedef struct s_object
{
	enum e_object_type	type;
	t_vector3f			position;
	t_color				albedo;
	float				radius;
	float				height;
	t_vector3f			normal;
}	t_object;

typedef struct s_objects
{
	t_object			*data;
	size_t				length;
	size_t				size;
}	t_objects;

typedef struct s_sphere {
	t_vector3f	origin;
	float		radius;
	t_vector3f	color;
}	t_sphere;

//t_sphere	sphere_create(t_vector3f origin, float radius, t_vector3f color);
//bool		hit_sphere(t_ray ray, t_sphere sphere);
//float		get_hit_scalar_sphere(t_ray ray, t_sphere sphere);
float	hit_sphere(t_ray ray, t_object sphere);

int	initialize_objects_array(t_objects *objects, size_t size);
int	add_object_in_objects(t_objects *objects, t_object object);
int	remove_object_in_objects(t_objects *objects, size_t index);
int	free_objects(t_objects *objects);

t_object	sphere_create(t_vector3f origin, float radius, t_vector3f albedo);

void	print_object2(t_object object);

#endif //OBJECT_H
