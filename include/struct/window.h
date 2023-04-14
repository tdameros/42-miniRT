#ifndef WINDOW_H
# define WINDOW_H

# include "t_dialog_box.h"

typedef struct s_window
{
	void			*mlx;
	void			*window;
	t_dialog_boxes	dialog_boxes;
}	t_window;

#endif //WINDOW_H
