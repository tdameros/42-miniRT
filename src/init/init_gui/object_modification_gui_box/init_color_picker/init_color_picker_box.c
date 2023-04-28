#include "t_gui_box.h"

int	init_color_picker_box(t_minirt *minirt, t_gui_box *gui_box,
		t_gui_box *parent)
{
	*gui_box = create_t_gui_box(minirt, parent, \
		(t_point_int_2d){
			.x = 0,
			.y = 0}, \
		(t_size_int_2d){
			.width = parent->size.width,
			.height = parent->size.height / 2 - 2});

}
