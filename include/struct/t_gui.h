#ifndef T_GUI_H
# define T_GUI_H

# include <stdbool.h>

# include "struct/t_gui_boxes.h"
# include "struct/t_image.h"
# include "struct/t_point_int_2d.h"

typedef struct s_gui
{
	bool		is_hidden;
	double		hidden_ratio;
	t_gui_boxes	gui_boxes;
	bool		color_picker_base_color_was_changed;
	t_color		color_picker_base_color;
	void		(*draw_gui_image)(t_image *destination, \
					const t_image *source, t_point_int_2d position);
}	t_gui;

#endif //T_GUI_H
