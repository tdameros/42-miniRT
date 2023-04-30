#ifndef T_GUI_BOX_H
# define T_GUI_BOX_H

# include <unistd.h>

# include "t_image.h"
# include "struct/t_minirt.h"
# include "struct/t_point_int_2d.h"
# include "struct/t_size_int_2d.h"
# include "struct/t_gui_boxes.h"

typedef struct s_gui_box
{
	struct s_gui_box	*parent;
	t_point_int_2d		position;
	t_size_int_2d		size;
	t_image				image;
	// TODO add on hover image
	void				(*draw)(struct s_gui_box *self, t_minirt *minirt,
							int x_offset, int y_offset);
	void				(*on_click)(struct s_gui_box *self, t_minirt *minirt,
							int y, int x);
	t_gui_boxes			children;
}	t_gui_box;

t_gui_box	create_t_gui_box(t_minirt *minirt, t_gui_box *parent,
				t_point_int_2d position, t_size_int_2d size);
void		destroy_t_gui_box(t_window *window, t_gui_box *gui_box);

void		default_gui_box_draw(t_gui_box *self, t_minirt *minirt,
				int x_offset, int y_offset);
void		default_gui_box_on_click(t_gui_box *self, t_minirt *minirt, int y,
				int x);

t_gui_box	*get_clicked_gui_box(t_gui_boxes gui_boxes, int *x, int *y);

#endif //T_GUI_BOX_H
