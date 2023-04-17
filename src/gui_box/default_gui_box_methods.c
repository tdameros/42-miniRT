#include "mlx.h"

#include "struct/t_gui_box.h"
#include "struct/t_minirt.h"

void	default_gui_box_draw(t_gui_box *self, t_minirt *minirt,
			int x_offset, int y_offset)
{
	mlx_put_image_to_window(minirt->window.mlx, minirt->window.window,
							self->image.image, self->position.x + x_offset,
							self->position.y + y_offset);
}
