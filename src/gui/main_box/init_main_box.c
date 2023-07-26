#include <sys/errno.h>
#include <stdlib.h>

#include "gui/box.h"
#include "colors.h"
#include "gui/main_gui_box.h"
#include "gui/UI.h"

static int	init_main_gui_box_children(t_engine *engine, t_gui_box *gui_box);

int	init_main_gui_box(t_engine *engine, t_gui_box *gui_box)
{
	*gui_box = create_t_gui_box(engine, (t_gui_box_create){NULL,
			(t_vector2i){.x = 12, \
						.y = 12},
			(t_vector2i){.x = engine->window.size.x - 24, \
						.y = engine->window.size.y / 8}, true});
	if (errno == EINVAL)
		return (-1);
	change_image_color(&gui_box->image, BASE_GUI_COLOR);
	round_image_corners(&gui_box->image, BOX_ROUNDING_RADIUS);
	gui_box->draw = &default_gui_box_draw;
	gui_box->on_click = &default_gui_box_on_click;
	if (init_main_gui_box_children(engine, gui_box) < 0)
		return (-1); // TODO Free stuff
	return (0);
}

static int	init_main_gui_box_children(t_engine *engine, t_gui_box *gui_box)

{
	gui_box->children.size = 2;
	gui_box->children.data = malloc(sizeof(*gui_box->children.data)
			* gui_box->children.size);
	if (gui_box->children.data == NULL)
		return (-1);
	if (init_object_creation_gui_box(engine, gui_box->children.data, gui_box) < 0)
	{
		free(gui_box->children.data);
		return (-1);
	}
	if (init_menu_gui_box(engine, gui_box->children.data + 1, gui_box) < 0)
	{
		// TODO free object creation gui box
		free(gui_box->children.data);
		return (-1);
	}
	return (0);
}
