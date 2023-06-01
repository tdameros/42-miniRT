#include <sys/errno.h>
#include <stdlib.h>

#include "gui/box.h"
#include "colors.h"
#include "gui/object_modification_box.h"

static int	init_object_modification_gui_box_children(t_engine *engine,
				t_gui_box *parent);

int	init_object_modification_gui_box(t_engine *engine, t_gui_box *gui_box,
		const t_gui_box *object_creation_gui_box)
{
	*gui_box = create_t_gui_box(engine, NULL, \
		(t_vector2i){
			.x = WINDOW_WIDTH - WINDOW_WIDTH / 4 \
				- object_creation_gui_box->position.x,
			.y = object_creation_gui_box->size.y \
				+ object_creation_gui_box->position.y * 2}, \
		(t_vector2i){
			.x = WINDOW_WIDTH / 4, \
			.y = WINDOW_HEIGHT \
				- (object_creation_gui_box->size.y \
				+ object_creation_gui_box->position.y * 3)});
	if (errno == EINVAL)
		return (-1);
	change_image_color(&gui_box->image, 0x40000000);
	round_image_corners(&gui_box->image, 20);
	gui_box->draw = &default_gui_box_draw;
	gui_box->on_click = &default_gui_box_on_click;
	if (init_object_modification_gui_box_children(engine, gui_box))
		return (-1); // TODO free image
	return (0);
}

static int	init_object_modification_gui_box_children(t_engine *engine,
				t_gui_box *parent) {
	parent->children.size = 2;
	parent->children.data = malloc(sizeof(*parent->children.data)
			* parent->children.size);
	if (parent->children.data == NULL)
		return (ft_print_error("Failed to allocate gui_box children"), -1);
	if (init_rgb_picker(engine, parent->children.data, parent) < 0)
	{
		free(parent->children.data);
		return (-1);
	}
	if (init_object_attributes_modification_box(engine,
			parent->children.data + 1, parent) < 0)
	{
		free(parent->children.data); // TODO free previous box
		return (-1);
	}
	return (0);
}
