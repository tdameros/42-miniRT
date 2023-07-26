#include <stdlib.h>
#include <math.h>
#include "errno.h"

#include "gui/box.h"
#include "gui/main_gui_box.h"
#include "gui/utils.h"
#include "gui/UI.h"
#include "engine.h"
#include "colors.h"

#define NUMBER_OF_OBJECT_TYPES 5

static int	init_object_creation_children(t_engine *engine, t_gui_box *gui_box);
static void	init_object_creation_box(const t_engine *engine, t_gui_box *gui_box,
				int type);

int	init_object_creation_gui_box(t_engine *minirt, t_gui_box *gui_box,
		t_gui_box *parent)
{
	*gui_box = create_t_gui_box(minirt, (t_gui_box_create){parent,
			(t_vector2i){8, 8},
			(t_vector2i){.y = parent->size.y - 16, \
							.x = parent->size.x / 4 * 3 - 16}, true});
	if (errno == EINVAL || errno == ENOMEM)
		return (-1);
	gui_box->draw = &default_gui_box_draw;
	gui_box->on_click = &default_gui_box_on_click;
	change_image_color(&gui_box->image, SUB_GUI_COLOR);
	round_image_corners(&gui_box->image, BOX_ROUNDING_RADIUS);
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
		if (init_image(&gui_box->children.data[i].image, &engine->window,
				gui_box->children.data[i].size.x, gui_box->children.data[i].size.y) < 0)
			return (-1); // TODO free stuff
		if (init_image(&gui_box->children.data[i].on_hover_image, &engine->window,
				gui_box->children.data[i].size.x, gui_box->children.data[i].size.y) < 0)
			return (-1); // TODO free stuff
	}
	init_object_creation_box(engine, gui_box->children.data + 0, SPHERE);
	init_object_creation_box(engine, gui_box->children.data + 1, PLANE);
	init_object_creation_box(engine, gui_box->children.data + 2, CYLINDER);
	init_object_creation_box(engine, gui_box->children.data + 3, CONE);
	init_object_creation_box(engine, gui_box->children.data + 4, LIGHT);
	engine->gui.object_creation_boxes = &gui_box->children;
	return (0);
}

static void	init_object_creation_box(const t_engine *engine, t_gui_box *gui_box,
				const int type)
{
	change_image_color(&gui_box->image, COLOR_TRANSPARENT);
	change_image_color(&gui_box->on_hover_image, HOVER_GUI_COLOR);
	draw_icon(&gui_box->image, type, COLOR_TRANSPARENT,
		engine->gui.material_to_assign_to_new_objects);
	draw_icon(&gui_box->on_hover_image, type, HOVER_GUI_COLOR,
		engine->gui.material_to_assign_to_new_objects);
	round_image_corners(&gui_box->on_hover_image, BOX_ROUNDING_RADIUS);
	round_image_corners(&gui_box->image, BOX_ROUNDING_RADIUS);
	if (type == SPHERE)
		gui_box->on_click = &sphere_create_on_click;
	else if (type == PLANE)
		gui_box->on_click = &plane_create_on_click;
	else if (type == CYLINDER)
		gui_box->on_click = &cylinder_create_on_click;
	else if (type == CONE)
		gui_box->on_click = &cone_create_on_click;
	else
		gui_box->on_click = &light_create_on_click;
}
