#include "mlx.h"

#include "struct/t_gui_box.h"
#include "colors.h"

static bool	mouse_is_hovering_box(t_gui_box *self, t_minirt *minirt,
				int x_offset, int y_offset);

void	icon_box_draw_method(t_gui_box *self, t_minirt *minirt,
			int x_offset, int y_offset)
{
	if (mouse_is_hovering_box(self, minirt, x_offset, y_offset))
		mlx_put_image_to_window(minirt->window.mlx, minirt->window.window,
			self->image.image,
			self->position.x + x_offset,
			self->position.y + y_offset);
	if (self->children.data != NULL && self->children.data->draw != NULL) // TODO remove if
		self->children.data->draw(self->children.data, minirt,
			x_offset + self->position.x, y_offset + self->position.y);
}

static bool	mouse_is_hovering_box(t_gui_box *self, t_minirt *minirt,
				int x_offset, int y_offset)
{
	t_point_int_2d	mouse_position_in_parent;

	mlx_mouse_get_pos(minirt->window.window,
		&mouse_position_in_parent.x, &mouse_position_in_parent.y);
	mouse_position_in_parent.x -= x_offset;
	mouse_position_in_parent.y -= y_offset;
	return (mouse_position_in_parent.x >= self->position.x
		&& mouse_position_in_parent.x < self->position.x + self->size.width
		&& mouse_position_in_parent.y >= self->position.y
		&& mouse_position_in_parent.y < self->position.y + self->size.height
		&& get_image_pixel_color(&self->image,
				mouse_position_in_parent.y - self->position.y,
				mouse_position_in_parent.x - self->position.x)
			!= COLOR_TRANSPARENT);
}
