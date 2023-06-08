#include <errno.h>
#include <stdlib.h>

#include "engine.h"
#include "gui/box.h"
#include "colors.h"
#include "gui/object_modification_box.h"

static int	init_rgb_picker_children(t_engine *minirt, t_gui_boxes *gui_boxes,
				t_gui_box *parent);

int	init_rgb_picker(t_engine *minirt, t_gui_box *gui_box)
{
	if (init_rgb_picker_children(minirt, &gui_box->children, gui_box) < 0)
		return (-1); // TODO free previous gui_box
	gui_box->draw = &default_gui_box_draw;
	gui_box->on_click = &default_gui_box_on_click;
	change_image_color(&gui_box->image, COLOR_TRANSPARENT);
	return (0);
}

static int	init_rgb_picker_children(t_engine *minirt, t_gui_boxes *gui_boxes,
				t_gui_box *parent)
{
	gui_boxes->size = 2;
	gui_boxes->data = malloc(sizeof(*gui_boxes->data) * gui_boxes->size);
	if (gui_boxes->data == NULL)
		return (-1);
	if (init_base_color_box(minirt, gui_boxes->data, parent) < 0)
	{
		free(gui_boxes->data);
		return (-1);
	}
	if (init_color_picker_box(minirt, gui_boxes->data + 1, parent) < 0)
		return (-1); //TODO free previous
	change_image_color(&gui_boxes->data[0].on_hover_image, COLOR_TRANSPARENT);
	change_image_color(&gui_boxes->data[1].on_hover_image, COLOR_TRANSPARENT);
	return (0);
}
