#include <stdlib.h>
#include <math.h>
#include "errno.h"

#include "gui/box.h"
#include "gui/main_gui_box.h"
#include "gui/utils.h"
#include "engine.h"
#include "colors.h"

#define NUMBER_OF_OBJECT_TYPES 3

static int	init_object_creation_children(t_engine *engine, t_gui_box *gui_box);
static void	init_sphere_creation_box(t_gui_box *gui_box);

int	init_object_creation_gui_box(t_engine *minirt, t_gui_box *gui_box,
		t_gui_box *parent)
{
	*gui_box = create_t_gui_box(minirt, parent, (t_vector2i){8, 8},
			(t_vector2i){.y = parent->size.y - 16, \
							.x = parent->size.x / 4 * 3 - 16});
	if (errno == EINVAL || errno == ENOMEM)
		return (-1);
	if (gui_box->image.data == NULL)
		return (-1);
	gui_box->draw = &default_gui_box_draw;
	gui_box->on_click = &default_gui_box_on_click;
	change_image_color(&gui_box->image, 0x40202020);
	round_image_corners(&gui_box->image, 20);
	if (init_object_creation_children(minirt, gui_box) < 0)
	{
		destroy_t_image(&minirt->window, &gui_box->image);
		ft_bzero(gui_box, sizeof(*gui_box));
		return (-1);
	}
	return (0);
}

static int	init_object_creation_children(t_engine *engine, t_gui_box *gui_box)
{
	int	i;

	if (create_n_horizontal_boxes(engine, gui_box, NUMBER_OF_OBJECT_TYPES,
			(t_boxes_offsets){ICON_BOX_SEPARATOR, ICON_BOX_SEPARATOR}) < 0)
		return (-1);
	i = -1;
	while (++i < NUMBER_OF_OBJECT_TYPES)
	{
		if (init_image(&gui_box->children.data[i].on_hover_image, &engine->window,
				gui_box->children.data[i].size.x, gui_box->children.data[i].size.y) < 0)
			return (-1); // TODO free stuff
		change_image_color(&gui_box->children.data[i].image, COLOR_TRANSPARENT);
		round_image_corners(&gui_box->children.data[i].image, ICON_BOX_ROUNDING_RADIUS);
		change_image_color(&gui_box->children.data[i].on_hover_image, ICON_BOX_COLOR);
		round_image_corners(&gui_box->children.data[i].on_hover_image, ICON_BOX_ROUNDING_RADIUS);
		gui_box->children.data[i].draw = &icon_box_draw_method;
	}
	init_sphere_creation_box(gui_box->children.data + 0);
	return (0);
}

static void	init_sphere_creation_box(t_gui_box *gui_box)
{
	change_image_color(&gui_box->image, COLOR_TRANSPARENT);
	change_image_color(&gui_box->on_hover_image, ICON_BOX_COLOR);

	draw_circle_with_shadow(&gui_box->image,
		(t_vector2i){gui_box->size.x / 2, gui_box->size.y / 2},
		gui_box->size.y / 2 - gui_box->size.y / 10, get_t_color_from_uint(COLOR_BLUE));

	draw_circle_with_shadow(&gui_box->on_hover_image,
		(t_vector2i){gui_box->size.x / 2, gui_box->size.y / 2},
		gui_box->size.y / 2 - gui_box->size.y / 10, get_t_color_from_uint(COLOR_BLUE));

	round_image_corners(&gui_box->on_hover_image, ICON_BOX_ROUNDING_RADIUS);
	round_image_corners(&gui_box->image, ICON_BOX_ROUNDING_RADIUS);

	gui_box->on_click = &sphere_create_on_click;
}
