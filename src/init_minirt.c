#include <stddef.h>
#include <stdlib.h>

#include "libft.h"
#include "mlx.h"

#include "gui/init.h"
#include "events.h"
#include "parsing.h"
#include "hooks.h"
#include "render_frame.h"
#include "window.h"
#include "engine.h"
#include "font/render.h"

#define DEFAULT_MAX_RESOLUTION_REDUCTION 21
#define DEFAULT_MIN_RESOLUTION_REDUCTION 1

static void	init_hooks(t_engine *engine);

int	init_engine(t_engine *engine, const char *start_up_scene, const char **argv)
{
	ft_bzero(engine, sizeof(t_engine));
	engine->argv = argv;
	engine->antialiasing = true;
	engine->quality.max_reduction = DEFAULT_MAX_RESOLUTION_REDUCTION;
	engine->quality.min_reduction = DEFAULT_MIN_RESOLUTION_REDUCTION;
	get_screen_size(&engine->window.size.x, &engine->window.size.y); // TODO check that screen size is not too small
//	printf("%i, %i\n", engine->window.size.x, engine->window.size.y);
//	exit(0);
	engine->window.mlx = mlx_init();
	if (engine->window.mlx == NULL)
		return (-1);
	engine->window.window = mlx_new_window(engine->window.mlx,
			engine->window.size.x, engine->window.size.y, "miniRT");
	if (engine->window.window == NULL)
		return (-1); // TODO: free mlx

	init_image(&engine->ray_traced_image, &engine->window,
		engine->window.size.x, engine->window.size.y);
	engine->raytraced_pixels.data = malloc(sizeof(*engine->raytraced_pixels.data) * engine->ray_traced_image.size); // TODO secure
	ft_bzero(engine->raytraced_pixels.data, sizeof(*engine->raytraced_pixels.data) * engine->ray_traced_image.size); // TODO remove me
	engine->raytraced_pixels.size = engine->ray_traced_image.size;
	engine->raytraced_pixels.width = engine->ray_traced_image.width;
	engine->raytraced_pixels.height = engine->ray_traced_image.height;

	engine->should_render_ray_tracing = true;
	engine->should_render_at_full_resolution = true;

	init_image(&engine->main_image, &engine->window, engine->window.size.x,
		engine->window.size.y);
	change_image_color(&engine->main_image, COLOR_BLACK);

	init_image(&engine->gui.screen_shot.image, &engine->window,
		engine->window.size.x, engine->window.size.y);

	init_hooks(engine);

	if (get_font(&engine->gui.font, "assets/fonts/Envy Code R PR7/Envy Code R.ttf") < 0)
		return (-1); // TODO free everything
	init_gui(engine);
	if (parse_scene(engine, start_up_scene) < 0)
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
	mlx_loop_hook(engine->window.mlx, &render_frame, engine);
}
