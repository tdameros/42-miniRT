#include <sys/errno.h>

#include "struct/t_gui_box.h"
#include "init.h"

int	init_object_modification_gui_box(t_minirt *minirt, t_gui_box *gui_box,
		const t_gui_box *object_creation_gui_box)
{
	*gui_box = create_t_gui_box(minirt, NULL,
			(t_point_int_2d){.x = WINDOW_WIDTH - WINDOW_WIDTH / 4 - object_creation_gui_box->position.x,
							 .y = object_creation_gui_box->size.height + object_creation_gui_box->position.y * 2},
			(t_size_int_2d){.width = WINDOW_WIDTH / 4, \
							.height = WINDOW_HEIGHT - (object_creation_gui_box->size.height + object_creation_gui_box->position.y * 3)});
	if (errno == EINVAL)
		return (-1);
	change_image_color(&gui_box->image, 0x40000000);
	round_image_corners(&gui_box->image, 20);
	gui_box->draw = &default_gui_box_draw;
	gui_box->on_click = &default_gui_box_on_click;
	return (0);
}
