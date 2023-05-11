#include "mlx.h"

#include "gui/box.h"
#include "engine.h"

#if defined __linux__

void	default_gui_box_draw(t_gui_box *self, t_engine *minirt,
			int x_offset, int y_offset)
{
	size_t	i;

	minirt->gui.draw_gui_image(&minirt->main_image, &self->image,
		(t_vector2i){\
			.x = self->position.x + x_offset, \
			.y = self->position.y + y_offset}
	);
	i = self->children.size;
	while (i--)
		if (self->children.data[i].draw != NULL)
			self->children.data[i].draw(self->children.data + i, minirt,
				x_offset + self->position.x, y_offset + self->position.y);
}
#elif defined __APPLE__

void	default_gui_box_draw(t_gui_box *self, t_engine *minirt,
			int x_offset, int y_offset)
{
	size_t	i;

	mlx_put_image_to_window(minirt->window.mlx, minirt->window.window,
		self->image.data, self->position.x + x_offset,
		self->position.y + y_offset);
	i = self->children.size;
	while (i--)
		if (self->children.data[i].draw != NULL)
			self->children.data[i].draw(self->children.data + i, minirt,
				x_offset + self->position.x, y_offset + self->position.y);
}
#else
# error "Unsuported OS"
#endif

void	default_gui_box_on_click(t_gui_box *self, t_engine *minirt, int y,
			int x)
{
	t_gui_box	*clicked_gui_box;

	clicked_gui_box = get_clicked_gui_box(self->children, &x, &y);
	if (clicked_gui_box != NULL && clicked_gui_box->on_click != NULL)
		clicked_gui_box->on_click(clicked_gui_box, minirt, y, x);
}