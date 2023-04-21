#include <stdbool.h>

#include "struct/t_gui_box.h"

static bool	is_point_in_gui_box(const t_gui_box *gui_box, int x, int y);

t_gui_box	*get_clicked_gui_box(t_gui_boxes gui_boxes, int *x, int *y)
{
	size_t	i;

	i = gui_boxes.length;
	while (i--)
	{
		if (is_point_in_gui_box(gui_boxes.data + i, *x, *y))
		{
			*x -= gui_boxes.data[i].position.x;
			*y -= gui_boxes.data[i].position.y;
			return (gui_boxes.data + i);
		}
	}
	return (NULL);
}

static bool	is_point_in_gui_box(const t_gui_box *gui_box, int x, int y)
{
	return (x >= gui_box->position.x
			&& x < gui_box->position.x + gui_box->size.width
			\
		&& y >= gui_box->position.y
			&& y < gui_box->position.y + gui_box->size.height);
}
