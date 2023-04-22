#include <sys/errno.h>
#include <stdlib.h>

#include "struct/t_gui_box.h"
#include "colors.h"
#include "init.h"

static int	init_main_gui_box_children(t_minirt *minirt, t_gui_box *gui_box);

int	init_main_gui_box(t_minirt *minirt, t_gui_box *gui_box)
{
	*gui_box = create_t_gui_box(minirt, NULL,
			(t_point_int_2d){.x = 12, \
							 .y = 12},
			(t_size_int_2d){.width = WINDOW_WIDTH - 24, \
							.height = WINDOW_HEIGHT / 8});
	if (errno == EINVAL)
		return (-1);
	change_image_color(&gui_box->image, 0x40000000);
	round_image_corners(&gui_box->image, 20);
	gui_box->draw = &default_gui_box_draw;
	gui_box->on_click = &default_gui_box_on_click;

	if (init_main_gui_box_children(minirt, gui_box) < 0)
		return (-1); // TODO Free stuff
	return (0);
}

static int	init_main_gui_box_children(t_minirt *minirt, t_gui_box *gui_box)

{
	gui_box->children.size = 1;
	gui_box->children.length = 1;
	gui_box->children.data = malloc(sizeof(*gui_box->children.data)
		* gui_box->children.size);
	if (gui_box->children.data == NULL)
		return (-1);
	// init object creation gui box
	if (init_menu_gui_box(minirt, gui_box->children.data, gui_box) < 0)
	{
		// TODO free object creation gui box
		free(gui_box->children.data);
		return (-1);
	}
	return (0);
}
