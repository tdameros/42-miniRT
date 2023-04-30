#ifndef T_MINIRT_H
# define T_MINIRT_H

# include "struct/t_window.h"
# include "struct/t_raytracing_data.h"
# include "struct/t_gui.h"
# include "t_image.h"

typedef struct s_minirt
{
	t_window			window;
	t_gui				gui;
	t_image				main_image;
	t_raytracing_data	raytracing_data;
}	t_minirt;

#endif //T_MINIRT_H
