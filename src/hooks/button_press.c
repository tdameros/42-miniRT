#include "libft.h" // TODO remove when stop using

#include "miniRT_X11.h"
#include "struct/t_minirt.h"
#include "struct/t_gui_box.h"

static t_gui_box	*get_clicked_gui_box(t_gui_boxes gui_boxes, int *x, int *y);
static bool			is_point_in_gui_box(const t_gui_box *gui_box, int x, int y);

int	button_press_handler(int button, int x, int y, t_minirt *minirt)
{
	t_gui_box	*clicked_gui_box;

	if (button != BUTTON_LEFT)
		return (0);
	clicked_gui_box = get_clicked_gui_box(minirt->gui_boxes, &x, &y);
	if (clicked_gui_box != NULL && clicked_gui_box->on_click != NULL)
		clicked_gui_box->on_click(clicked_gui_box, minirt, y, x);
	return (0);
}

static t_gui_box	*get_clicked_gui_box(t_gui_boxes gui_boxes, int *x, int *y)
{
	size_t	i;

	i = gui_boxes.size;
	while (i--)
	{
		if (is_point_in_gui_box(gui_boxes.gui_boxes + i, *x, *y))
		{
			*x -= gui_boxes.gui_boxes[i].position.x;
			*y -= gui_boxes.gui_boxes[i].position.y;
			if (gui_boxes.gui_boxes[i].children.size == 0)
				return (gui_boxes.gui_boxes + i);
			return (get_clicked_gui_box(gui_boxes.gui_boxes[i].children,
					x,
					y));
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
