#include "window.h"
#include "gui/box.h"

void	destroy_t_gui_boxes(t_window *window, t_gui_boxes *gui_boxes)
{
	if (gui_boxes->data != NULL)
	{
		while (gui_boxes->size--)
			destroy_t_gui_box(window, gui_boxes->data + gui_boxes->size);
		free(gui_boxes->data);
		gui_boxes->data = NULL;
	}
	gui_boxes->size = 0;
}
