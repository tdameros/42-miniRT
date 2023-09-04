#include <stdlib.h>

#include "mlx.h"

#include "engine.h"
#include "gui/box.h"

static void	destroy_gui(t_engine *minirt);

int	close_engine(t_engine *engine)
{
	destroy_gui(engine);
	destroy_t_image(&engine->window, &engine->main_image);
	if (engine->window.mlx != NULL && engine->window.window != NULL)
		mlx_destroy_window(engine->window.mlx, engine->window.window);
	// TODO destroy font
	exit(0); // TODO: free everything
}

static void	destroy_gui(t_engine *minirt)
{
	while (minirt->gui.gui_boxes.size--)
		destroy_t_gui_box(&minirt->window,
			minirt->gui.gui_boxes.data + minirt->gui.gui_boxes.size);
	free(minirt->gui.gui_boxes.data);
	free(minirt->gui.fps.fps_count);
}
