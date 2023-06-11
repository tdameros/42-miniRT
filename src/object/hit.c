/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:46:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/18 21:46:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer/ray.h"
#include "object.h"

float	hit_object(t_ray ray, t_object object)
{
	if (object.type == SPHERE)
		return (hit_sphere(ray, object));
	else if (object.type == PLANE)
		return (hit_plane(ray, object));
	return (-1);
}