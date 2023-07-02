#include <stdlib.h>
#include <errno.h>

#include "engine.h"
#include "gui/box.h"
#include "gui/main_gui_box.h"
#include "window.h"
#include "libft.h"
#include "gui/object_modification_box.h"

int init_gui_boxes(t_engine *minirt)
{
	minirt->gui.draw_gui_image = &put_image_to_image_unsafe;
	minirt->gui.gui_boxes.size = 2;
	minirt->gui.gui_boxes.data = malloc(sizeof(*minirt->gui.gui_boxes.data)
			* minirt->gui.gui_boxes.size);
	minirt->gui.object_modification_amount = 0.1f;
	minirt->gui.object_rotation_degrees = 10.0f;
	minirt->gui.fps.fps_count = ft_itoa(0); // TODO secure me
	minirt->gui.fps.last_update = get_current_time();
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
