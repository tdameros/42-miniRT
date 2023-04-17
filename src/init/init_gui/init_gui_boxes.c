#include <stdlib.h>
#include <errno.h>

#include "struct/t_minirt.h"
#include "struct/t_gui_box.h"
#include "struct/t_window.h"
#include "init.h"

int init_gui_boxes(t_minirt *minirt)
{
	minirt->gui_boxes.size = 2;
	minirt->gui_boxes.gui_boxes = malloc(sizeof(*minirt->gui_boxes.gui_boxes)
			* minirt->gui_boxes.size);
	if (minirt->gui_boxes.gui_boxes == NULL)
		return (-1);
	if (init_object_creation_gui_box(minirt,
			minirt->gui_boxes.gui_boxes) < 0)
	{
		free(minirt->gui_boxes.gui_boxes);
		return (-1);
	}
	if (init_object_modification_gui_box(minirt,
			minirt->gui_boxes.gui_boxes + 1, minirt->gui_boxes.gui_boxes) < 0)
	{
		// TODO free first gui box
		free(minirt->gui_boxes.gui_boxes);
		return (-1);
	}
	return (0);
}
