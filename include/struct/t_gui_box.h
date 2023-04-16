#ifndef T_GUI_BOX_H
#define T_GUI_BOX_H

# include <unistd.h>

# include "image.h"
# include "struct/t_point_int_2d.h"
# include "struct/t_size_int_2d.h"

typedef struct s_gui_boxes
{
	struct s_gui_box	*dialog_boxes;
	size_t				size;
}	t_gui_boxes;

typedef struct s_gui_box
{
	struct s_gui_box	*parent;
	t_point_int_2d		position;
	t_size_int_2d		size;
	t_image				image;
	t_gui_boxes			children;
}	t_gui_box;

#endif //T_GUI_BOX_H
