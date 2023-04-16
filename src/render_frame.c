#include "struct/t_minirt.h"
#include "mlx.h"

static void put_user_interface_to_window(t_minirt *minirt);

int	render_frame(t_minirt *minirt)
{
	for (int i = 0; i < WINDOW_WIDTH; i++)
		for (int j = 0; j < WINDOW_HEIGHT; j++)
			put_pixel_on_img(&minirt->main_image, j, i, 0x000000);
	mlx_put_image_to_window(minirt->window.mlx, minirt->window.window,
		minirt->main_image.image, 0, 0);
	put_user_interface_to_window(minirt);
	mlx_put_image_to_window(minirt->window.mlx, minirt->window.window,
		minirt->dialog_boxes.dialog_boxes->image.image, minirt->dialog_boxes.dialog_boxes->position.x, minirt->dialog_boxes.dialog_boxes->position.y);
	return (0);
}

static void put_user_interface_to_window(t_minirt *minirt)
{
	(void)minirt;
}
