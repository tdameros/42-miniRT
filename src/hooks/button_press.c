#include "miniRT_X11.h"
#include "struct/t_minirt.h"
#include "struct/t_gui_box.h"

int	button_press_handler(int button, int x, int y, t_minirt *minirt)
{
	t_gui_box	*clicked_gui_box;

	if (button != BUTTON_LEFT)
		return (0);
	clicked_gui_box = get_clicked_gui_box(minirt->gui.gui_boxes, &x, &y);
	if (clicked_gui_box != NULL && clicked_gui_box->on_click != NULL)
		clicked_gui_box->on_click(clicked_gui_box, minirt, y, x);
	return (0);
}
