#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "libft.h"
#include "mlx.h"

#include "gui/init.h"
#include "gui/utils.h"
#include "events.h"
#include "parsing.h"
#include "hooks.h"
#include "render_frame.h"
#include "window.h"
#include "engine.h"
#include "colors.h"
#include "font/render.h"

static void	init_hooks(t_engine *minirt);

static void	print_scene_content(t_raytracing_data *raytracing_data);
int	init_engine(t_engine *minirt, const char *start_up_scene)
{
	ft_bzero(minirt, sizeof(t_engine));
	minirt->window.mlx = mlx_init();
	if (minirt->window.mlx == NULL)
		return (-1);
	minirt->window.window = mlx_new_window(minirt->window.mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "miniRT");
	if (minirt->window.window == NULL)
		return (-1); // TODO: free mlx
	if (parse_scene(minirt, start_up_scene) < 0)
		return (-1); // TODO free stuff
	print_scene_content(&minirt->raytracing_data);

	init_image(&minirt->ray_traced_image, &minirt->window, WINDOW_WIDTH, WINDOW_HEIGHT); // TODO secure me

	init_image(&minirt->main_image, &minirt->window, WINDOW_WIDTH, WINDOW_HEIGHT); // TODO secure me
	change_image_color(&minirt->main_image, COLOR_BLACK);

	init_hooks(minirt);

	if (init_gui_boxes(minirt))
	{
		// TODO: free everything
		return (-1);
	}
	// TODO: secure me
	camera_create(&minirt->camera, vector2f_create(WINDOW_WIDTH, WINDOW_HEIGHT));
	init_scene(&minirt->scene);
//	if (get_font(&minirt->gui.font, "data/fonts/inconsolata/Inconsolata-VariableFont_wdth,wght.ttf") < 0)
//	if (get_font(&minirt->gui.font,
//			"data/fonts/Envy Code R PR7/Envy Code R.ttf") < 0)
//	if (get_font(&minirt->gui.font, "data/fonts/Roboto_Mono/RobotoMono-VariableFont_wght.ttf") < 0)
//	if (get_font(&minirt->gui.font, "data/fonts/JetBrains_Mono/JetBrainsMono-VariableFont_wght.ttf") < 0)
//	if (get_font(&minirt->gui.font, "data/fonts/Noto_Sans_Mono/NotoSansMono-VariableFont_wdth,wght.ttf") < 0)
	if (get_font(&minirt->gui.font, "data/fonts/Fira_Code/FiraCode-VariableFont_wght.ttf") < 0)
		return (-1); // TODO free everything
	return (0);
}

static void	init_hooks(t_engine *minirt)
{
	mlx_hook(minirt->window.window, KEY_PRESS, KEY_PRESS_MASK,
		&key_press_handler, minirt);
//	mlx_hook(minirt->window.window, KEY_RELEASE, KEY_RELEASE_MASK,
//		&key_release_handler, minirt);
	mlx_hook(minirt->window.window, BUTTON_PRESS, BUTTON_PRESS_MASK,
		&button_press_handler, minirt);
	mlx_hook(minirt->window.window, BUTTON_RELEASE, BUTTON_RELEASE_MASK,
		&button_release_handler, minirt);
	mlx_hook(minirt->window.window, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK,
			 &close_engine, minirt);
	mlx_loop_hook(minirt->window.mlx, &render_frame, minirt);
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
	printf("\tCamera FOV == %f\n", raytracing_data->camera.vertical_fov);
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
		print_vector(&object->normal);
	}
}
