/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:37:28 by vfries            #+#    #+#             */
/*   Updated: 2023/05/07 18:37:46 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "math/vector.h"
# include "scene.h"

t_color	render_pixel(t_engine *engine, int x, int y);
t_color	render_ray(t_ray ray, const t_scene *scene);
t_color	render_ray_icon(t_ray ray, const t_scene *scene,
			int *missed_object);
void	render_raytracing(t_engine *minirt, int incrementer);
void	render_anti_aliased_raytracing(t_engine *minirt);
void	render_icon(t_engine *minirt, unsigned int background_color);
//t_vector3f	render_ray(t_vector3f ray_origin, t_vector3f ray_direction);

void	interpolate_ray_tracing(t_raytraced_pixels *pixels,
			int incrementer);

#endif
