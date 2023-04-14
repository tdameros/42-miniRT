#ifndef DIALOG_BOX_H
# define DIALOG_BOX_H

# include <unistd.h>

# include "struct/t_point_int_2d.h"
# include "struct/t_size_int_2d.h"
# include "image.h"

typedef struct s_dialog_boxes
{
	struct s_dialog_box	*dialog_boxes;
	size_t				size;
}	t_dialog_boxes;

typedef struct s_dialog_box
{
	struct s_dialog_box	*parent;
	t_point_int_2d		position;
	t_size_int_2d		size;
	t_image				image;
	t_dialog_boxes		children;
	void				(*on_click)(struct s_dialog_box *self, void *arg);
	void				*arg;
}	t_dialog_box;

#endif //DIALOG_BOX_H
