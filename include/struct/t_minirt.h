#ifndef T_MINIRT_H
# define T_MINIRT_H

#include "struct/t_window.h"
#include "struct/t_gui_boxes.h"
#include "image.h"

typedef struct s_minirt
{
	t_window	window;
	t_gui_boxes	gui_boxes;
	t_image		main_image;
}	t_minirt;

#endif //T_MINIRT_H
