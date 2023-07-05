#include <errno.h>
#include <math.h>

#include "mlx.h"

#include "gui/box.h"
#include "gui/utils.h"
#include "gui/object_modification_box.h"

static void			color_picker_draw(t_gui_box *self, t_engine *minirt,
						int x_offset, int y_offset);
static void			update_image(t_gui_box *self, t_engine *minirt);
static unsigned int	get_darker_color(float x, float limit,
						t_color base_color);
static unsigned int	get_lighter_color(float x, float limit, float start,
						t_color base_color);
static void			color_picker_on_click(t_gui_box *self, t_engine *engine,
						int y, int x);

int	init_color_picker_box(t_engine *minirt, t_gui_box *gui_box,
		t_gui_box *parent)
{
	*gui_box = create_t_gui_box(minirt, parent, \
		(t_vector2i){
			.x = 0,
			.y = 0}, \
		(t_vector2i){
			.x = parent->size.x,
			.y = parent->size.y / 2 - 4});
	if (errno == EINVAL)
		return (-1);
	if (init_image(&gui_box->on_hover_image,
			&minirt->window, parent->size.x, parent->size.y / 2 - 4)
		< 0)
		return (-1); // TODO free previous image
	gui_box->draw = &color_picker_draw;
	gui_box->on_click = &color_picker_on_click;
	return (0);
}
#if defined __linux__

static void	color_picker_draw(t_gui_box *self, t_engine *minirt,
				int x_offset, int y_offset)
{
	if (minirt->gui.color_picker_base_color_was_changed)
	{
		update_image(self, minirt);
		minirt->gui.color_picker_base_color_was_changed = false;
	}
	minirt->gui.draw_gui_image(&minirt->main_image, &self->image,
		(t_point_int_2d){\
			.x = self->position.x + x_offset, \
			.y = self->position.y + y_offset}
	);
	if (mouse_is_hovering_box(&self->image, get_mouse_position(self, minirt,
				x_offset, y_offset)) == false)
		return ;
	add_hover_color_circle(self, minirt, x_offset, y_offset);
	minirt->gui.draw_gui_image(&minirt->main_image, &self->on_hover_image,
		(t_vector2i){\
			.x = self->position.x + x_offset, \
			.y = self->position.y + y_offset});
}
#elif defined __APPLE__

static void	color_picker_draw(t_gui_box *self, t_engine *minirt,
				int x_offset, int y_offset)
{
	if (minirt->gui.color_picker_base_color_was_changed)
	{
		update_image(self, minirt);
		minirt->gui.color_picker_base_color_was_changed = false;
	}
	mlx_put_image_to_window(minirt->window.mlx, minirt->window.window,
		self->image.data, self->position.x + x_offset,
		self->position.y + y_offset);
	if (mouse_is_hovering_box(&self->image, get_mouse_position_in_box(self, minirt,
			x_offset, y_offset)) == false)
		return ;
	add_hover_color_circle(self, minirt, x_offset, y_offset);
	mlx_put_image_to_window(minirt->window.mlx, minirt->window.window,
		self->on_hover_image.data, self->position.x + x_offset,
		self->position.y + y_offset);
}
#else
# error "Unsuported OS"
#endif

static void	update_image(t_gui_box *self, t_engine *minirt)
{
	int	y;
	int	x;
	int	limit;

	y = -1;
	while (++y < self->image.height)
	{
		x = -1;
		limit = (int)roundf((float)self->image.width / 2);
		while (++x < limit)
			put_pixel_on_image(&self->image, y, x, get_darker_color(x, limit,
					minirt->gui.color_picker_base_color));
		x--;
		while (++x < self->image.width)
			put_pixel_on_image(&self->image, y, x, get_lighter_color(x,
					self->image.width, limit,
					minirt->gui.color_picker_base_color));
	}
	round_image_corners(&self->image, 10);
}

static unsigned int	get_darker_color(float x, float limit,
						t_color base_color)
{
	const t_color	color = {
		.x = (int)roundf((float)base_color.x * x / limit),
		.y = (int)roundf((float)base_color.y * x / limit),
		.z = (int)roundf((float)base_color.z * x / limit),
	};

	return (rgb_to_uint(color));
}

static unsigned int	get_lighter_color(float x, float limit, float start,
						t_color base_color)
{
	const t_color	color = {
		.x = (int)roundf((float)base_color.x
			+ (255.0 - (float)base_color.x) * (x - start) / (limit - start)),
		.y = (int)roundf((float)base_color.y
			+ (255.0 - (float)base_color.y) * (x - start) / (limit - start)),
		.z = (int)roundf((float)base_color.z
			+ (255.0 - (float)base_color.z) * (x - start) / (limit - start)),
	};

	return (rgb_to_uint(color));
}

static void	color_picker_on_click(t_gui_box *self, t_engine *engine, int y,
				int x)
{
	const unsigned int	color = get_image_pixel_color(&self->image, y, x);

	if (color == COLOR_TRANSPARENT || engine->gui.selected_object == NULL)
		return ;
	engine->gui.selected_object->material.albedo = get_t_color_from_uint(color);
	engine->gui.selected_object->material.albedo.x /= 255.f;
	engine->gui.selected_object->material.albedo.y /= 255.f;
	engine->gui.selected_object->material.albedo.z /= 255.f;
}
