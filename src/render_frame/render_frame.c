#include "mlx.h"

#include "struct/t_minirt.h"
#include "struct/t_gui_box.h"
#include "render_frame.h"

int	render_frame(t_minirt *minirt)
{
	// Do ray tracing on minirt->main_image.image
	mlx_put_image_to_window(minirt->window.mlx, minirt->window.window,
		minirt->main_image.image, 0, 0);
	render_user_interface(minirt);
	return (0);
}
