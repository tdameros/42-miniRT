#include "struct/t_minirt.h"
#include "mlx.h"

static void put_user_interface_to_window(t_minirt *minirt);
static void	put_gui_box_to_window(const t_gui_box *gui_box,
				const t_minirt *minirt, int y, int x);

int	render_frame(t_minirt *minirt)
{
	for (int i = 0; i < WINDOW_WIDTH; i++)
		for (int j = 0; j < WINDOW_HEIGHT; j++)
			put_pixel_on_img(&minirt->main_image, j, i, 0x000000);
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

static void	put_gui_box_to_window(const t_gui_box *gui_box,
				const t_minirt *minirt, int x, int y)
{
	size_t	i;

	mlx_put_image_to_window(minirt->window.mlx, minirt->window.window,
		gui_box->image.image, gui_box->position.x + x, gui_box->position.y + y);
	i = gui_box->children.size;
	while (i--)
		put_gui_box_to_window(gui_box->children.gui_boxes + i, minirt,
			gui_box->position.x, gui_box->position.y);
}
