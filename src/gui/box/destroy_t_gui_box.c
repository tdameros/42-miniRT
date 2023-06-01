#include <stdlib.h>

#include "mlx.h"

#include "window.h"
#include "gui/box.h"

void	destroy_t_gui_box(t_window *window, t_gui_box *gui_box)
{
	if (gui_box->image.data != NULL)
		mlx_destroy_image(window->mlx, gui_box->image.data);
	gui_box->image = (t_image){0};
	if (gui_box->on_hover_image.data != NULL)
		mlx_destroy_image(window->mlx, gui_box->on_hover_image.data);
	gui_box->on_hover_image = (t_image){0};
	while (gui_box->children.size--)
		destroy_t_gui_box(window,
			gui_box->children.data + gui_box->children.size);
	gui_box->children.size = 0;
	free(gui_box->children.data);
	gui_box->children.data = NULL;
}
