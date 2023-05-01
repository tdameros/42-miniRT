#include <stdlib.h>

#include "mlx.h"

#include "struct/t_window.h"
#include "struct/t_gui_box.h"

void	destroy_t_gui_box(t_window *window, t_gui_box *gui_box)
{
	if (gui_box->image.data != NULL)
		mlx_destroy_image(window->mlx, gui_box->image.data);
	if (gui_box->on_hover_image.data != NULL)
		mlx_destroy_image(window->mlx, gui_box->on_hover_image.data);
	while (gui_box->children.size--)
		destroy_t_gui_box(window,
			gui_box->children.data + gui_box->children.size);
	free(gui_box->children.data);
}
