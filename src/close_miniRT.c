#include <stdlib.h>

#include "mlx.h"

#include "struct/t_minirt.h"
#include "struct/t_gui_box.h"

static void	destroy_gui(t_minirt *minirt);
static void	destroy_raytracing_data(t_raytracing_data *raytracing_data);

int	close_minirt(t_minirt *minirt)
{
	destroy_gui(minirt);
	destroy_raytracing_data(&minirt->raytracing_data);
	destroy_t_image(&minirt->window, &minirt->main_image);
	mlx_destroy_window(minirt->window.mlx, minirt->window.window);
	exit(0); // TODO: free everything
}

static void	destroy_gui(t_minirt *minirt)
{
	while (minirt->gui.gui_boxes.size--)
		destroy_t_gui_box(&minirt->window,
			minirt->gui.gui_boxes.data + minirt->gui.gui_boxes.size);
	free(minirt->gui.gui_boxes.data);
	free(minirt->gui.fps.fps_count);
}

static void	destroy_raytracing_data(t_raytracing_data *raytracing_data)
{
	free(raytracing_data->objects.data);
}
