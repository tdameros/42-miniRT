#include <errno.h>
#include <stdlib.h>
#include <math.h>

#include "struct/t_minirt.h"
#include "struct/t_gui_box.h"
#include "init.h"

static int	init_menu_gui_box_children(t_minirt *minirt, t_gui_box *gui_box);
static int	init_camera_icon_box(t_minirt *minirt, t_gui_box *gui_box,
				t_gui_box *parent);
static int	init_saving_icon_box(t_minirt *minirt, t_gui_box *gui_box,
				t_gui_box *parent);
static int	init_menu_settings_icon_box(t_minirt *minirt, t_gui_box *gui_box,
				t_gui_box *parent);

#define SEPARATOR 4
#define ICON_BOX_COLOR 0x40404040

int	init_menu_gui_box(t_minirt *minirt, t_gui_box *gui_box,
		t_gui_box *parent)
{
	*gui_box = create_t_gui_box(minirt, NULL,
		(t_point_int_2d){
			.x = parent->size.width - parent->size.width / 4, \
			.y = 8},
		(t_size_int_2d){
			.width = parent->size.width / 4 - 8, \
			.height = parent->size.height - 16
		}
	);
	if (errno == EINVAL)
		return (-1);
	change_image_color(&gui_box->image, 0x40202020);
	round_image_corners(&gui_box->image, 20);
	gui_box->draw = &default_gui_box_draw;
	gui_box->on_click = &default_gui_box_on_click;
	if (init_menu_gui_box_children(minirt, gui_box) < 0)
		return (-1); // TODO free image
	return (0);
}

static int	init_menu_gui_box_children(t_minirt *minirt, t_gui_box *gui_box)
{
	(void)minirt;
	(void)gui_box;
	gui_box->children.size = 3;
	gui_box->children.data = malloc(sizeof(*gui_box->children.data)
			* gui_box->children.size);
	if (gui_box->children.data == NULL)
		return (-1);
	if (init_camera_icon_box(minirt, gui_box->children.data + 0, gui_box) < 0)
		return (-1);
	if (init_saving_icon_box(minirt, gui_box->children.data + 1, gui_box) < 0)
		return (-1); // TODO free previous
	if (init_menu_settings_icon_box(minirt, gui_box->children.data + 2, gui_box) < 0)
		return (-1); // TODO free previous
	return (0);
}

static int	init_camera_icon_box(t_minirt *minirt, t_gui_box *gui_box,
				t_gui_box *parent)
{
	const int	box_width = round(((double)parent->size.width - SEPARATOR * 4)
								   / 3.0);

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

static int	init_saving_icon_box(t_minirt *minirt, t_gui_box *gui_box,
				t_gui_box *parent)
{
	const int	box_width = round(((double)parent->size.width - SEPARATOR * 4)
								   / 3.0);

	*gui_box = create_t_gui_box(minirt, NULL, \
		(t_point_int_2d){
			.x = SEPARATOR * 2 + box_width, \
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

static int	init_menu_settings_icon_box(t_minirt *minirt, t_gui_box *gui_box,
				t_gui_box *parent)
{
	const int	box_width = round(((double)parent->size.width - SEPARATOR * 4)
			/ 3.0);

	*gui_box = create_t_gui_box(minirt, NULL, \
		(t_point_int_2d){
			.x = SEPARATOR * 3 + box_width * 2, \
			.y = SEPARATOR
		}, \
		(t_size_int_2d){
			.width = box_width, \
			.height = parent->size.height - SEPARATOR * 2
		} \
	);
	if (errno == EINVAL)
		return (-1);
	if (init_settings_icon(minirt, gui_box) < 0)
		return (-1); // TODO free icon_box
	change_image_color(&gui_box->image, ICON_BOX_COLOR);
	round_image_corners(&gui_box->image, 20);
	gui_box->draw = &icon_box_draw_method;
	gui_box->on_click = &default_gui_box_on_click;
	return (0);
}
