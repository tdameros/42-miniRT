#include <sys/errno.h>
#include <stdlib.h>

#include "struct/t_gui_box.h"
#include "init.h"
#include "colors.h"

static int	init_object_modification_gui_box_children(t_minirt *minirt,
				t_gui_box *parent);
static int	init_rgb_picker(t_minirt *minirt, t_gui_box *gui_box,
				t_gui_box *parent);
static int	init_rgb_picker_children(t_minirt *minirt, t_gui_boxes *gui_boxes,
				t_gui_box *parent);

int	init_object_modification_gui_box(t_minirt *minirt, t_gui_box *gui_box,
		const t_gui_box *object_creation_gui_box)
{
	*gui_box = create_t_gui_box(minirt, NULL, \
		(t_point_int_2d){
			.x = WINDOW_WIDTH - WINDOW_WIDTH / 4 \
				- object_creation_gui_box->position.x,
			.y = object_creation_gui_box->size.height \
				+ object_creation_gui_box->position.y * 2}, \
		(t_size_int_2d){
			.width = WINDOW_WIDTH / 4, \
			.height = WINDOW_HEIGHT \
				- (object_creation_gui_box->size.height \
					+ object_creation_gui_box->position.y * 3)});
	if (errno == EINVAL)
		return (-1);
	change_image_color(&gui_box->image, 0x40000000);
	round_image_corners(&gui_box->image, 20);
	gui_box->draw = &default_gui_box_draw;
	gui_box->on_click = &default_gui_box_on_click;
	if (init_object_modification_gui_box_children(minirt, gui_box))
		return (-1); // TODO free image
	return (0);
}

static int	init_object_modification_gui_box_children(t_minirt *minirt,
				t_gui_box *parent) {
	parent->children.size = 1;
	parent->children.data = malloc(sizeof(*parent->children.data)
			* parent->children.size);
	if (init_rgb_picker(minirt, parent->children.data, parent) < 0)
	{
		free(parent->children.data);
		return (-1);
	}
	return (0);
}

static int	init_rgb_picker(t_minirt *minirt, t_gui_box *gui_box,
				t_gui_box *parent)
{
	*gui_box = create_t_gui_box(minirt, parent, \
		(t_point_int_2d){
			.x = 8,
			.y = parent->size.height - parent->size.height / 6}, \
		(t_size_int_2d){
			.width = parent->size.width - 16,
			.height = parent->size.height / 6 - 8});
	if (errno == EINVAL)
		return (-1);
	if (init_rgb_picker_children(minirt, &gui_box->children, gui_box) < 0)
		return (-1); // TODO free previous gui_box
	gui_box->draw = &default_gui_box_draw;
	gui_box->on_click = &default_gui_box_on_click;
	change_image_color(&gui_box->image, COLOR_TRANSPARENT);
	return (0);
}

static int	init_rgb_picker_children(t_minirt *minirt, t_gui_boxes *gui_boxes,
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
	return (0);
}
