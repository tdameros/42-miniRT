#include <stdlib.h>
#include <math.h>
#include "errno.h"

#include "gui/box.h"
#include "gui/main_gui_box.h"
#include "engine.h"
#include "colors.h"

static int	init_object_creation_children(t_engine *minirt, t_gui_box *gui_box);
static int	init_sphere_icon_box(t_engine *minirt, t_gui_box *gui_box,
								   t_gui_box *parent);
static int	init_cylinder_icon_box(t_engine *minirt, t_gui_box *gui_box,
									 t_gui_box *parent);
static int	init_plane_icon_box(t_engine *minirt, t_gui_box *gui_box,
								  t_gui_box *parent);

int	init_object_creation_gui_box(t_engine *minirt, t_gui_box *gui_box,
									t_gui_box *parent)
{
	*gui_box = create_t_gui_box(minirt, parent, (t_vector2i){8, 8},
			(t_vector2i){.y = parent->size.y - 16, \
							.x = parent->size.x / 4 * 3 - 16});
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

static int	init_object_creation_children(t_engine *minirt, t_gui_box *gui_box)
{
	gui_box->children.size = 3;
	gui_box->children.data = malloc(sizeof(*gui_box->children.data)
			* gui_box->children.size);
	if (gui_box->children.data == NULL)
		return (-1);
	if (init_sphere_icon_box(minirt, gui_box->children.data, gui_box) < 0)
	{
		free(gui_box->children.data);
		return (-1);
	}
	if (init_cylinder_icon_box(minirt, gui_box->children.data + 1, gui_box) < 0)
	{
		// TODO free previous
		free(gui_box->children.data);
		return (-1);
	}
	if (init_plane_icon_box(minirt, gui_box->children.data + 2, gui_box) < 0)
	{
		// TODO free previous
		free(gui_box->children.data);
		return (-1);
	}
	return (0);
}

static int	init_sphere_icon_box(t_engine *minirt, t_gui_box *gui_box,
								   t_gui_box *parent)
{
	const int	box_width = roundf(((float)parent->size.x - ICON_BOX_SEPARATOR * 4)
			/ 3.f);

	*gui_box = create_t_gui_box(minirt, NULL, \
		(t_vector2i){
			.x = ICON_BOX_SEPARATOR, \
			.y = ICON_BOX_SEPARATOR
		}, \
		(t_vector2i){
			.x = box_width, \
			.y = parent->size.y - ICON_BOX_SEPARATOR * 2
		} \
	);
	if (errno == EINVAL)
		return (-1);
	if (init_image(&gui_box->on_hover_image, &minirt->window,
				   gui_box->size.x, gui_box->size.y) < 0)
		return (-1); // TODO free stuff
	change_image_color(&gui_box->image, COLOR_TRANSPARENT);
	round_image_corners(&gui_box->image, ICON_BOX_ROUNDING_RADIUS);
	change_image_color(&gui_box->on_hover_image, ICON_BOX_COLOR);
	round_image_corners(&gui_box->on_hover_image, ICON_BOX_ROUNDING_RADIUS);
//	if (init_sphere_icon(minirt, gui_box) < 0)
//		return (-1); // TODO free icon_box image
	gui_box->draw = &icon_box_draw_method;
	gui_box->on_click = &default_gui_box_on_click;
	return (0);
}

static int	init_cylinder_icon_box(t_engine *minirt, t_gui_box *gui_box,
									 t_gui_box *parent)
{
	const int	box_width = round(((double)parent->size.x - ICON_BOX_SEPARATOR * 4)
			/ 3.0);

	*gui_box = create_t_gui_box(minirt, NULL, \
		(t_vector2i){
			.x = ICON_BOX_SEPARATOR * 2 + box_width, \
			.y = ICON_BOX_SEPARATOR
		}, \
		(t_vector2i){
			.x = box_width, \
			.y = parent->size.y - ICON_BOX_SEPARATOR * 2
		} \
	);
	if (errno == EINVAL)
		return (-1);
	if (init_image(&gui_box->on_hover_image, &minirt->window,
				   gui_box->size.x, gui_box->size.y) < 0)
		return (-1); // TODO free stuff
	change_image_color(&gui_box->image, COLOR_TRANSPARENT);
	round_image_corners(&gui_box->image, ICON_BOX_ROUNDING_RADIUS);
	change_image_color(&gui_box->on_hover_image, ICON_BOX_COLOR);
	round_image_corners(&gui_box->on_hover_image, ICON_BOX_ROUNDING_RADIUS);
//	if (init_settings_icon(minirt, gui_box) < 0)
//		return (-1); // TODO free icon_box image
	gui_box->draw = &icon_box_draw_method;
	gui_box->on_click = &default_gui_box_on_click;
	return (0);
}

static int	init_plane_icon_box(t_engine *minirt, t_gui_box *gui_box,
								  t_gui_box *parent)
{
	const int	box_width = round(((double)parent->size.x - ICON_BOX_SEPARATOR * 4)
			/ 3.0);

	*gui_box = create_t_gui_box(minirt, NULL, \
		(t_vector2i){
			.x = ICON_BOX_SEPARATOR * 3 + box_width * 2, \
			.y = ICON_BOX_SEPARATOR
		}, \
		(t_vector2i){
			.x = box_width, \
			.y = parent->size.y - ICON_BOX_SEPARATOR * 2
		} \
	);
	if (errno == EINVAL)
		return (-1);
	if (init_image(&gui_box->on_hover_image, &minirt->window,
				   gui_box->size.x, gui_box->size.y) < 0)
		return (-1); // TODO free stuff
	change_image_color(&gui_box->image, COLOR_TRANSPARENT);
	round_image_corners(&gui_box->image, ICON_BOX_ROUNDING_RADIUS);
	change_image_color(&gui_box->on_hover_image, ICON_BOX_COLOR);
	round_image_corners(&gui_box->on_hover_image, ICON_BOX_ROUNDING_RADIUS);
//	if (init_settings_icon(minirt, gui_box) < 0)
//		return (-1); // TODO free icon_box image
	gui_box->draw = &icon_box_draw_method;
	gui_box->on_click = &default_gui_box_on_click;
	return (0);
}
