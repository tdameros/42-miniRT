#ifndef MINIRT_STRUCT_H
# define MINIRT_STRUCT_H

# include "window.h"
# include "t_dialog_box.h"

typedef struct s_minirt
{
	t_window		window;
	t_dialog_boxes	dialog_boxes;
}	t_minirt;

#endif //MINIRT_STRUCT_H
