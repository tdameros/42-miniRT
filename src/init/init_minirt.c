#include <stddef.h>

#include "libft.h"
#include "mlx.h"

#include "miniRT_X11.h"
#include "hooks.h"
#include "render_frame.h"
#include "close_miniRT.h"
#include "struct/t_window.h"
#include "struct/t_minirt.h"
#include "init.h"

static void	init_hooks(t_minirt *minirt);

#include <stdlib.h>
static void	print_scene_content(t_raytracing_data *raytracing_data);
int	init_minirt(t_minirt *minirt, const char *start_up_scene)
{
	(void)start_up_scene; // TODO remove me

	ft_bzero(minirt, sizeof(t_minirt));
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
	exit(0);

	init_image_from_xpm(&minirt->main_image, &minirt->window, "data/test.xpm"); // TODO secure me


	init_hooks(minirt);

	if (init_gui_boxes(minirt))
	{
		// TODO: free everything
		return (-1);
	}
	return (0);
}

static void	init_hooks(t_minirt *minirt)
{
	mlx_hook(minirt->window.window, KEY_PRESS, KEY_PRESS_MASK,
		&key_press_handler, minirt);
//	mlx_hook(minirt->window.window, KEY_RELEASE, KEY_RELEASE_MASK,
//		&key_release_handler, minirt);
	mlx_hook(minirt->window.window, BUTTON_PRESS, BUTTON_PRESS_MASK,
		&button_press_handler, minirt);
	mlx_hook(minirt->window.window, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK,
		&close_minirt, minirt);
	mlx_loop_hook(minirt->window.mlx, &render_frame, minirt);
}

static void print_color(t_color *color);
static void	print_vector(t_vector_3d *vector);
static void	print_object(t_object *object);
#include <stdio.h>
static void	print_scene_content(t_raytracing_data *raytracing_data)
{
	printf("Ambient lightning\n");
	printf("\tAmbient lightning ratio == %f\n",
		raytracing_data->ambient_light.lighting_ratio);
	printf("\tAmbient lightning color\n");
	print_color(&raytracing_data->ambient_light.color);
	printf("Camera\n");
	printf("\tCamera position\n");
	print_vector(&raytracing_data->camera.position);
	printf("\tCamera orientation\n");
	print_vector(&raytracing_data->camera.orientation);
	printf("\tCamera FOV == %f\n", raytracing_data->camera.fov);
	printf("Light\n");
	printf("\tLight position\n");
	print_vector(&raytracing_data->light.position);
	printf("\tLight brightness == %f\n", raytracing_data->light.brightness);
	printf("\tLight color\n");
	print_color(&raytracing_data->light.color);
	for (size_t i = 0; i < raytracing_data->objects.length; i++)
		print_object(&raytracing_data->objects.data[i]);
}

static void print_color(t_color *color)
{
	printf("\t\t\tr == %d\n", color->r);
	printf("\t\t\tg == %d\n", color->g);
	printf("\t\t\tb == %d\n", color->b);
}

static void	print_vector(t_vector_3d *vector)
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
	print_color(&object->color);
	if (object->type == SPHERE || object->type == CYLINDER)
		printf("\tDiameter == %f\n", object->diameter);
	if (object->type == CYLINDER)
		printf("\tHeight == %f\n", object->height);
	if (object->type == PLANE || object->type == CYLINDER)
	{
		printf("\tNormal\n");
		print_vector(&object->normal);
	}
}
