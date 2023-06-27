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
# include <stdbool.h>

# include "math/vector.h"
# include "colors.h"

enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CYLINDER_INF,
};

typedef struct s_material
{

	t_vector3f	albedo;
	float		reflect;
	float		specular;
	float		roughness;
	bool		is_checked_pattern;
	t_vector3f	checked_pattern_albedo;
	t_vector2f	checked_pattern_size;

}	t_material;

typedef struct s_object
{
	enum e_object_type	type;
	t_vector3f			position;
	float				radius;
	float				height;
	t_vector3f			normal;
	t_material			material;
}	t_object;

typedef struct s_objects
{
	t_object			*data;
	size_t				length;
	size_t				size;
}	t_objects;


int	initialize_objects_array(t_objects *objects, size_t size);
int	add_object_in_objects(t_objects *objects, t_object object);
int	remove_object_in_objects(t_objects *objects, size_t index);
int	free_objects(t_objects *objects);

t_object	sphere_create(t_vector3f origin, float radius, t_material material);
t_object	plane_create(t_vector3f position, t_vector3f normal, t_material material);
t_object cylinder_infinite_create(t_vector3f origin, t_vector3f axe,
		float radius, t_material material);

t_object cylinder_create(t_vector3f origin, t_vector3f axe, float radius, float height, t_material material);
void	print_object2(t_object object);

t_material	material_create(t_vector3f albedo, float roughness, float metallic);

#endif //OBJECT_H
