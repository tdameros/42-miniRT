#ifndef T_GUI_H
# define T_GUI_H

# include <stdbool.h>

# include "struct/t_gui_boxes.h"

typedef struct s_gui
{
	bool		is_hidden;
	double		hidden_ratio;
	t_gui_boxes	gui_boxes;
	t_color		color_picker_base_color;
}	t_gui;

#endif //T_GUI_H
