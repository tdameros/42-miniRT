#ifndef INIT_H
# define INIT_H

# include "struct/t_gui_box.h"
# include "struct/t_minirt.h"

int			init_gui_boxes(t_minirt *minirt);
t_gui_box	create_t_gui_box(t_minirt *minirt, t_gui_box *parent,
				t_point_int_2d position, t_size_int_2d size);

#endif //INIT_H
