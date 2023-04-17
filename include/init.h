#ifndef INIT_H
# define INIT_H

# include "struct/t_gui_box.h"
# include "struct/t_minirt.h"

int	init_gui_boxes(t_minirt *minirt);
int	init_object_creation_gui_box(t_minirt *minirt, t_gui_box *gui_box);
int	init_object_modification_gui_box(t_minirt *minirt, t_gui_box *gui_box,
		const t_gui_box *object_creation_gui_box);

#endif //INIT_H
