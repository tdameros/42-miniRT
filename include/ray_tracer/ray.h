/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:39:16 by vfries            #+#    #+#             */
/*   Updated: 2023/05/07 18:39:23 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#ifndef RAY_H
# define RAY_H

# include "math/vector.h"

typedef struct s_ray
{
	t_vector3f	origin;
	t_vector3f	direction;
}	t_ray;

//	ray.c
t_ray		ray_create(t_vector3f origin, t_vector3f direction);
//t_point_3d	ray_at(t_ray ray, float t);
//
//t_color		ray_color(t_ray r);

#endif
