#ifndef MINIRT_INIT_H
# define MINIRT_INIT_H

# include "struct/t_gui_box.h"
# include "struct/t_minirt.h"

int				init_dialog_boxes(t_minirt *minirt);
t_gui_box	create_t_dialog_box(t_minirt *minirt,
								 t_gui_box *parent, const t_point_int_2d position,
								 const t_size_int_2d size);

#endif //MINIRT_INIT_H
