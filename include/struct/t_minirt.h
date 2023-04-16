#ifndef T_MINIRT_H
#define T_MINIRT_H

#include "t_window.h"
#include "t_gui_box.h"

typedef struct s_minirt
{
	t_window	window;
	t_gui_boxes	gui_boxes;
	t_image		main_image;
}	t_minirt;

#endif //T_MINIRT_H
