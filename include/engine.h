/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:18:38 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/25 19:22:04 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "gui/gui.h"
# include "image.h"
# include "ray_tracer/camera.h"
# include "scene.h"
# include "window.h"

#ifdef __linux__
# define IS_LINUX 1
#else
# define IS_LINUX 0
#endif

# define NB_OF_MOVEMENT_KEYS 8
# define DEFAULT_DISTANCE_OF_NEW_OBJECTS 10.f

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

enum e_effect
{
	NO_EFFECT,
	BLACK_AND_WHITE,
	NEGATIVE_BLACK_AND_WHITE,
	NEGATIVE,
	END_EFFECT,
};

typedef struct s_engine
{
	t_window				window;
	t_vector2i				mouse_position;
	t_gui					gui;
	t_image					main_image;
	t_image					ray_traced_image;
	t_image					bvh_image;
	t_raytraced_pixels		raytraced_pixels;
	t_camera				camera;
	t_scene					scene;
	t_object_being_placed	object_being_placed;
	char					*start_up_scene;
	float					object_being_placed_distance;
	t_vector2i				previous_mouse_position;
	int						pressed_keys[NB_OF_MOVEMENT_KEYS];
	int						pressed_keys_index;
	bool					command_key_is_pressed;
	bool					should_render_ray_tracing;
	bool					should_render_at_full_resolution;
	bool					antialiasing;
	bool					scene_changed;
	bool					display_bounding_box;
	enum e_effect			post_processing_effect;
	t_quality				quality;
	uint64_t				last_frame_start_time;
}	t_engine;

//	close_engine/close_engine.c
int		close_engine(t_engine *engine);

//	close_engine/destroy_mlx.c
void	destroy_mlx(t_engine *engine);

// init/init_images.c
int	init_engine_images(t_engine *engine);

//	init/init_engine.c
int	init_engine(t_engine *engine, const char *start_up_scene,
		const char *path_to_minirt_binary);

// init/init_mlx.c
int	init_mlx(t_engine *engine);

// init/set_minirt_folder_as_current_working_directory.c
int	set_minirt_folder_as_current_working_directory(
		const char *path_to_minirt_binary);

#endif
