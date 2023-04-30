#include "mlx.h"

#include "struct/t_gui_box.h"
#include "init.h"

void	icon_box_draw_method(t_gui_box *self, t_minirt *minirt,
			int x_offset, int y_offset)
{
	if (mouse_is_hovering_box(self,
			get_mouse_position(self, minirt, x_offset, y_offset)))
		mlx_put_image_to_window(minirt->window.mlx, minirt->window.window,
			self->image.data,
			self->position.x + x_offset,
			self->position.y + y_offset);
	if (self->children.data != NULL && self->children.data->draw != NULL) // TODO remove if
		self->children.data->draw(self->children.data, minirt,
			x_offset + self->position.x, y_offset + self->position.y);
}
