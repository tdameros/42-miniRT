#include <stdio.h>
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
#include "init_scene.h"

#define DEFAULT_MAX_RESOLUTION_REDUCTION 21
#define DEFAULT_MIN_RESOLUTION_REDUCTION 1

static void	init_hooks(t_engine *engine);

static void	print_scene_content(t_raytracing_data *raytracing_data);
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
										   engine->window.size.x, engine->window.size.y,
										   "miniRT");
	if (engine->window.window == NULL)
		return (-1); // TODO: free mlx
	if (parse_scene(engine, start_up_scene) < 0)
		return (-1); // TODO free stuff
	print_scene_content(&engine->raytracing_data);

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

	// TODO: secure me
	camera_create(&engine->camera, vector2f_create(engine->window.size.x,
		engine->window.size.y));
//	if (get_font(&engine->gui.font, "data/fonts/inconsolata/Inconsolata-VariableFont_wdth,wght.ttf") < 0)
	if (get_font(&engine->gui.font, "data/fonts/Envy Code R PR7/Envy Code R.ttf") < 0)
//	if (get_font(&engine->gui.font, "data/fonts/Roboto_Mono/RobotoMono-VariableFont_wght.ttf") < 0)
//	if (get_font(&engine->gui.font, "data/fonts/JetBrains_Mono/JetBrainsMono-VariableFont_wght.ttf") < 0)
//	if (get_font(&engine->gui.font, "data/fonts/Noto_Sans_Mono/NotoSansMono-VariableFont_wdth,wght.ttf") < 0)
//	if (get_font(&engine->gui.font, "data/fonts/Fira_Code/FiraCode-VariableFont_wght.ttf") < 0)
		return (-1); // TODO free everything
	init_gui(engine);
	init_scene(engine);
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

static void print_color(t_color *color);
static void	print_vector(t_vector3f *vector);
static void	print_object(t_object *object);
#include <stdio.h>
static void	print_scene_content(t_raytracing_data *raytracing_data)
{
	printf("Ambient lightning\n");
	printf("\tAmbient lightning ratio == %f\n",
		raytracing_data->ambient_light.lighting_ratio);
	printf("\tAmbient lightning albedo\n");
	print_color(&raytracing_data->ambient_light.color);
	printf("Camera\n");
	printf("\tCamera position\n");
	print_vector(&raytracing_data->camera.position);
	printf("\tCamera orientation\n");
	print_vector(&raytracing_data->camera.direction);
	printf("\tCamera FOV == %f\n", raytracing_data->camera.horizontal_fov);
	printf("Light\n");
	printf("\tLight position\n");
	print_vector(&raytracing_data->light.position);
	printf("\tLight brightness == %f\n", raytracing_data->light.brightness);
	printf("\tLight albedo\n");
	print_color(&raytracing_data->light.color);
	for (size_t i = 0; i < raytracing_data->objects.length; i++)
		print_object(&raytracing_data->objects.data[i]);
}

static void print_color(t_color *color)
{
	printf("\t\t\tr == %f\n", color->x);
	printf("\t\t\tg == %f\n", color->y);
	printf("\t\t\tb == %f\n", color->z);
}

static void	print_vector(t_vector3f *vector)
{
	printf("\t\t\tx == %f\n", vector->x);
	printf("\t\t\ty == %f\n", vector->y);
	printf("\t\t\tz == %f\n", vector->z);
}

static void	print_object(t_object *object)
{
	if (object->type == SPHERE)
		printf("Sphere\n");
	else if (object->type == PLANE)
		printf("Plane\n");
	else if (object->type == CYLINDER)
		printf("Cylinder\n");
	printf("\tPosition\n");
	print_vector(&object->position);
	printf("\tColor\n");
	print_color(&object->material.albedo);
	if (object->type == SPHERE || object->type == CYLINDER)
		printf("\tDiameter == %f\n", object->radius);
	if (object->type == CYLINDER)
		printf("\tHeight == %f\n", object->height);
	if (object->type == PLANE || object->type == CYLINDER)
	{
		printf("\tNormal\n");
		print_vector(&object->axis);
	}
}
