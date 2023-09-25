/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:37:28 by vfries            #+#    #+#             */
/*   Updated: 2023/09/20 18:14:53 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "math/vector.h"
# include "scene.h"
# include "ray_tracer/rays.h"
# include "engine.h"

typedef struct s_raytracing_routine_args
{
	t_engine		*engine;
	int				current_line;
	int				incrementer;
}	t_raytracing_routine_args;

typedef struct s_render_raytraced_icon_routine_arg
{
	t_engine		*engine;
	int				current_line;
	unsigned int	background_color;
}	t_render_raytraced_icon_routine_arg;

typedef struct s_raytracing_anti_aliasing_routine_args
{
	t_engine		*engine;
	int				current_line;
}	t_raytracing_anti_aliasing_routine_args;

//	post_processing.c
t_vector3f	calculate_post_processing_color(const t_engine *engine,
				t_vector3f color);

//	render.c
void		render_raytracing(t_engine *minirt, int incrementer);

//	render_icon.c
void		render_icon(t_engine *minirt, unsigned int background_color);

//	render_with_anti_aliasing.c
void		render_anti_aliased_raytracing(t_engine *minirt);

//	render_ray.c
t_color		render_ray(t_ray ray, const t_scene *scene);
t_color		render_ray_icon(t_ray ray, const t_scene *scene,
				int *missed_object);

#endif
