#include "struct/t_minirt.h"
#include "mlx.h"

static void put_user_interface_to_window(t_minirt *minirt);
static void	put_gui_box_to_window(t_gui_box *gui_box,
				t_minirt *minirt, int x_offset, int y_offset);

int	render_frame(t_minirt *minirt)
{
	// Do ray tracing on minirt->main_image.image
	mlx_put_image_to_window(minirt->window.mlx, minirt->window.window,
		minirt->main_image.image, 0, 0);
	put_user_interface_to_window(minirt);
	return (0);
}

static void put_user_interface_to_window(t_minirt *minirt)
{
	size_t	i;

	i = minirt->gui_boxes.size;
	while (i--)
		put_gui_box_to_window(minirt->gui_boxes.gui_boxes + i, minirt, 0, 0);
}

static void	put_gui_box_to_window(t_gui_box *gui_box,
				t_minirt *minirt, int x_offset, int y_offset)
{
	size_t	i;

	gui_box->draw(gui_box, minirt, x_offset, y_offset);
	i = gui_box->children.size;
	while (i--)
		put_gui_box_to_window(gui_box->children.gui_boxes + i, minirt,
			gui_box->position.x, gui_box->position.y);
}
