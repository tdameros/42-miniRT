/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:18:38 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/31 09:18:52 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "deprecated/t_raytracing_data.h"
# include "gui/gui.h"
# include "image.h"
# include "ray_tracer/camera.h"
# include "scene.h"
# include "window.h"

# define NB_OF_THREADS 16
# define NB_OF_MOVEMENT_KEYS 8

typedef struct s_raytraced_pixels
{
	t_vector3f	*data;
	int			height;
	int			width;
	size_t		size;
}	t_raytraced_pixels;

typedef struct s_object_being_placed
{
	t_object	*object;
	t_light		*light;
}	t_object_being_placed;

typedef struct s_quality
{
	int	min_reduction;
	int	max_reduction;
}	t_quality;

typedef struct s_engine
{
	t_window				window;
	t_gui					gui;
	t_image					main_image;
	t_image					ray_traced_image;
	t_raytraced_pixels		raytraced_pixels;
	t_raytracing_data		raytracing_data;
	t_camera				camera;
	t_scene					scene;
	t_object_being_placed	object_being_placed;
	float					object_being_placed_distance;
	t_vector2i				previous_mouse_position;
	int						pressed_keys[NB_OF_MOVEMENT_KEYS];
	int						pressed_keys_index;
	bool					should_render_ray_tracing;
	bool					should_render_at_full_resolution;
	bool					antialiasing;
	bool					scene_changed;
	t_quality				quality;
	const char				**argv;
}	t_engine;

int		init_engine(t_engine *engine, const char *start_up_scene,
			const char **argv);
int		close_engine(t_engine *engine);

#endif //ENGINE_H
