#include <stddef.h>
#include <stdlib.h>

#include "libft.h"
#include "mlx.h"

#include "mlx_wrapper.h"
#include "gui/init.h"
#include "events.h"
#include "parsing.h"
#include "hooks.h"
#include "render_frame.h"
#include "window.h"
#include "engine.h"
#include "font/render.h"

#ifndef DEFAULT_MAX_RESOLUTION_REDUCTION
# define DEFAULT_MAX_RESOLUTION_REDUCTION 21
#endif
#ifndef DEFAULT_MIN_RESOLUTION_REDUCTION
# define DEFAULT_MIN_RESOLUTION_REDUCTION 1
#endif
#ifndef DEFAULT_ANTIALIASING_VALUE
# define DEFAULT_ANTIALIASING_VALUE true
#endif

static void	init_hooks(t_engine *engine);
static int	set_minirt_folder_as_current_working_directory(
				const char *path_to_minirt_binary);
static char	*get_path_to_minirt_folder(const char *path_to_minirt_binary);

int	init_engine(t_engine *engine, const char *start_up_scene,
		const char *path_to_minirt_binary)
{
	ft_bzero(engine, sizeof(t_engine));
	engine->start_up_scene = realpath(start_up_scene, NULL);
	if (engine->start_up_scene == NULL)
		return (-1);
	if (set_minirt_folder_as_current_working_directory(path_to_minirt_binary))
		return (free(engine->start_up_scene), -1);
	engine->post_processing_effect = NO_EFFECT;
	engine->antialiasing = DEFAULT_ANTIALIASING_VALUE;
	engine->quality.max_reduction = DEFAULT_MAX_RESOLUTION_REDUCTION;
	engine->quality.min_reduction = DEFAULT_MIN_RESOLUTION_REDUCTION;
	engine->window.mlx = mlx_init();
	if (engine->window.mlx == NULL)
		return (-1);
	get_screen_size(engine);
	engine->window.window = mlx_new_window(engine->window.mlx,
			engine->window.size.x, engine->window.size.y, "miniRT");
	if (engine->window.window == NULL)
		return (-1); // TODO: free mlx
	engine->window.is_focused = true;
	init_image(&engine->ray_traced_image, &engine->window,
		engine->window.size.x, engine->window.size.y);
	init_image(&engine->bvh_image, &engine->window,
			   engine->window.size.x, engine->window.size.y);
	engine->raytraced_pixels.data = malloc(sizeof(*engine->raytraced_pixels.data) * engine->ray_traced_image.size); // TODO secure
	ft_bzero(engine->raytraced_pixels.data, sizeof(*engine->raytraced_pixels.data) * engine->ray_traced_image.size); // TODO remove me
	engine->raytraced_pixels.size = engine->ray_traced_image.size;
	engine->raytraced_pixels.width = engine->ray_traced_image.width;
	engine->raytraced_pixels.height = engine->ray_traced_image.height;

	engine->should_render_ray_tracing = true;
	engine->should_render_at_full_resolution = true;
	engine->scene.render_shadows = true;

	init_image(&engine->main_image, &engine->window, engine->window.size.x,
		engine->window.size.y);
	change_image_color(&engine->main_image, COLOR_BLACK);

	init_image(&engine->gui.screen_shot.image, &engine->window,
		engine->window.size.x, engine->window.size.y);

	init_hooks(engine);

	if (get_font(&engine->gui.font, "assets/fonts/Envy Code R PR7/Envy Code R.ttf") < 0)
		return (-1); // TODO free everything
	init_gui(engine);
	// TODO secure it
	vectors_int_initialize(&engine->scene.plane_indexes, 5);
	if (parse_scene(engine, engine->start_up_scene) < 0)
		return (-1); // TODO free stuff
	return (0);
}

static void	init_hooks(t_engine *engine)
{
	mlx_hook(engine->window.window, KEY_PRESS, KEY_PRESS_MASK,
		&key_press_handler, engine);
	mlx_hook(engine->window.window, KEY_RELEASE, KEY_RELEASE_MASK,
		&key_release_handler, engine);
	mlx_hook(engine->window.window, BUTTON_PRESS, BUTTON_PRESS_MASK,
		&button_press_handler, engine);
	mlx_hook(engine->window.window, BUTTON_RELEASE, BUTTON_RELEASE_MASK,
		&button_release_handler, engine);
	mlx_hook(engine->window.window, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK,
		&close_engine, engine);
	mlx_hook(engine->window.window, FOCUS_IN, FOCUS_CHANGE_MASK,
		&focus_in_handler, engine);
	mlx_hook(engine->window.window, FOCUS_OUT, FOCUS_CHANGE_MASK,
		&focus_out_handler, engine);
	mlx_hook(engine->window.window, MOTION_NOTIFY, POINTER_MOTION_MASK,
		&motion_handler, engine);
	mlx_loop_hook(engine->window.mlx, &render_frame, engine);
}

static int	set_minirt_folder_as_current_working_directory(
				const char *path_to_minirt_binary)
{
	char	*path_to_minirt_folder;

	path_to_minirt_folder = get_path_to_minirt_folder(path_to_minirt_binary);
	if (path_to_minirt_folder == NULL)
		return (-1);
	if (chdir(path_to_minirt_folder) < 0)
	{
		free(path_to_minirt_folder);
		return (-1);
	}
	free(path_to_minirt_folder);
	return (0);
}

static char	*get_path_to_minirt_folder(const char *path_to_minirt_binary)
{
	char	*path_to_executable;
	char	*last_backslash;
	char	*path_to_minirt_folder;

	path_to_executable = realpath(path_to_minirt_binary, NULL);
	if (path_to_executable == NULL)
		return (NULL);
	last_backslash = ft_strrchr(path_to_executable, '/');
	if (last_backslash == NULL)
		path_to_minirt_folder = ft_strdup(path_to_executable);
	else
		path_to_minirt_folder = ft_substr(path_to_executable, 0,
				last_backslash - path_to_executable);
	free(path_to_executable);
	return (path_to_minirt_folder);
}
