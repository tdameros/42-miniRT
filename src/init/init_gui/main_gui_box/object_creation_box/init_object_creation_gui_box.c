#include <stdlib.h>
#include <math.h>
#include "errno.h"

#include "struct/t_minirt.h"
#include "struct/t_gui_box.h"
#include "init.h"

#define SEPARATOR 4
#define ICON_BOX_COLOR 0x40404040

static int	init_object_creation_children(t_minirt *minirt, t_gui_box *gui_box);
static int	init_sphere_creation_box(t_minirt *minirt, t_gui_box *gui_box,
				t_gui_box *parent);

int	init_object_creation_gui_box(t_minirt *minirt, t_gui_box *gui_box,
		t_gui_box *parent)
{
	*gui_box = create_t_gui_box(minirt, parent, (t_point_int_2d){8, 8},
			(t_size_int_2d){.height = parent->size.height - 16, \
							.width = parent->size.width / 4 * 3 - 16});
	if (errno == EINVAL)
		return (-1);
	if (gui_box->image.data == NULL)
		return (-1);
	gui_box->draw = &default_gui_box_draw;
	gui_box->on_click = &default_gui_box_on_click;
	change_image_color(&gui_box->image, 0x40202020);
	round_image_corners(&gui_box->image, 20);
	if (init_object_creation_children(minirt, gui_box) < 0)
	{
		// TODO free
		return (-1);
	}
	return (0);
}

static int	init_object_creation_children(t_minirt *minirt, t_gui_box *gui_box)
{
	gui_box->children.size = 1;
	gui_box->children.data = malloc(sizeof(*gui_box->children.data)
			* gui_box->children.size);
	if (gui_box->children.data == NULL)
		return (-1);
	if (init_sphere_creation_box(minirt, gui_box->children.data, gui_box) < 0)
	{
		free(gui_box->children.data);
		return (-1);
	}
	return (0);
}

static int	init_sphere_creation_box(t_minirt *minirt, t_gui_box *gui_box,
				t_gui_box *parent)
{
	const int	box_width = roundf(((float)parent->size.width - SEPARATOR * 4)
								   / 3.f);

	*gui_box = create_t_gui_box(minirt, NULL, \
		(t_point_int_2d){
			.x = SEPARATOR, \
			.y = SEPARATOR
		}, \
		(t_size_int_2d){
			.width = box_width, \
			.height = parent->size.height - SEPARATOR * 2
		} \
	);
	if (errno == EINVAL)
		return (-1);
	change_image_color(&gui_box->image, ICON_BOX_COLOR);
	round_image_corners(&gui_box->image, 20);
	gui_box->draw = &icon_box_draw_method;
	gui_box->on_click = &default_gui_box_on_click;
	return (0);
}
