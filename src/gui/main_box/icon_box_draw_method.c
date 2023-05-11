#include "mlx.h"

#include "gui/box.h"
#include "gui/utils.h"

#if defined __linux__

void	icon_box_draw_method(t_gui_box *self, t_engine *engine,
			int x_offset, int y_offset)
{
	if (mouse_is_hovering_box(self,
			get_mouse_position(self, engine, x_offset, y_offset)))
		engine->gui.draw_gui_image(&engine->main_image, &self->on_hover_image,
			(t_vector2i){\
				.x = self->position.x + x_offset, \
				.y = self->position.y + y_offset});
	else
		engine->gui.draw_gui_image(&engine->main_image, &self->image,
			(t_vector2i){\
				.x = self->position.x + x_offset, \
				.y = self->position.y + y_offset});
	if (self->children.data != NULL && self->children.data->draw != NULL) // TODO remove if
		self->children.data->draw(self->children.data, engine,
			x_offset + self->position.x, y_offset + self->position.y);
}
#elif defined __APPLE__

void	icon_box_draw_method(t_gui_box *self, t_engine *engine,
			int x_offset, int y_offset)
{
	if (mouse_is_hovering_box(self,
			get_mouse_position(self, engine, x_offset, y_offset)))
		mlx_put_image_to_window(engine->window.mlx, engine->window.window,
			self->on_hover_image.data, self->position.x + x_offset,
			self->position.y + y_offset);
	else
		mlx_put_image_to_window(engine->window.mlx, engine->window.window,
			self->image.data, self->position.x + x_offset,
			self->position.y + y_offset);
	if (self->children.data != NULL && self->children.data->draw != NULL) // TODO remove if
		self->children.data->draw(self->children.data, engine,
			x_offset + self->position.x, y_offset + self->position.y);
}
#else
# error "Unsuported OS"
#endif
