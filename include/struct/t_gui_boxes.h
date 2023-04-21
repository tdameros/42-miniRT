#ifndef T_GUI_BOXES_H
# define T_GUI_BOXES_H

# include <stddef.h>

typedef struct s_gui_boxes
{
	struct s_gui_box	*data;
	size_t				length;
	size_t				size;
}	t_gui_boxes;

#endif //T_GUI_BOXES_H
