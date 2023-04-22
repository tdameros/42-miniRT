#include <stdlib.h>
#include <errno.h>

#include "struct/t_minirt.h"
#include "struct/t_gui_box.h"
#include "struct/t_window.h"
#include "init.h"

int init_gui_boxes(t_minirt *minirt)
{
	minirt->gui.gui_boxes.size = 2;
	minirt->gui.gui_boxes.length = 2;
	minirt->gui.gui_boxes.data = malloc(sizeof(*minirt->gui.gui_boxes.data)
										* minirt->gui.gui_boxes.size);
	if (minirt->gui.gui_boxes.data == NULL)
		return (-1);
	if (init_main_gui_box(minirt,
						  minirt->gui.gui_boxes.data) < 0)
	{
		free(minirt->gui.gui_boxes.data);
		return (-1);
	}
	if (init_object_modification_gui_box(minirt,
										 minirt->gui.gui_boxes.data + 1, minirt->gui.gui_boxes.data) < 0)
	{
		// TODO free first gui box
		free(minirt->gui.gui_boxes.data);
		return (-1);
	}
	return (0);
}
