/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:41:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/07 15:41:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"
# include "ray.h"

typedef struct s_sphere {
	t_vector3	origin;
	double		radius;
	t_vector3	color;
}	t_sphere;

t_sphere	*sphere_create(t_vector3 origin, double radius, t_vector3 color);
bool		hit_sphere(t_ray ray, t_sphere sphere);
double		get_hit_scalar_sphere(t_ray ray, t_sphere sphere);

#endif