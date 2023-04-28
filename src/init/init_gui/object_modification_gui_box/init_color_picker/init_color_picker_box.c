#include <errno.h>
#include <math.h>

#include "mlx.h"

#include "struct/t_gui_box.h"
#include "init.h"

static void			color_picker_draw(t_gui_box *self, t_minirt *minirt,
						int x_offset, int y_offset);
static void			update_image(t_gui_box *self, t_minirt *minirt,
						int x_offset, int y_offset);
static unsigned int	get_darker_color(double x, double limit,
						t_color base_color);
static unsigned int	get_lighter_color(double x, double limit, double start,
						t_color base_color);

int	init_color_picker_box(t_minirt *minirt, t_gui_box *gui_box,
		t_gui_box *parent)
{
	*gui_box = create_t_gui_box(minirt, parent, \
		(t_point_int_2d){
			.x = 0,
			.y = 0}, \
		(t_size_int_2d){
			.width = parent->size.width,
			.height = parent->size.height / 2 - 4});
	if (errno == EINVAL)
		return (-1);
	gui_box->draw = &color_picker_draw;
	return (0);
}

static void	color_picker_draw(t_gui_box *self, t_minirt *minirt,
				int x_offset, int y_offset)
{
	update_image(self, minirt, x_offset, y_offset);
	mlx_put_image_to_window(minirt->window.mlx, minirt->window.window,
		self->image.image,
		self->position.x + x_offset,
		self->position.y + y_offset);
}

static void	update_image(t_gui_box *self, t_minirt *minirt,
				int x_offset, int y_offset)
{
	int	y;
	int	x;
	int	limit;

	y = -1;
	while (++y < self->image.height)
	{
		x = -1;
		limit = (int)round((double)self->image.width / 2);
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
	add_hover_color_circle(self, minirt, x_offset, y_offset);
}

static unsigned int	get_darker_color(double x, double limit,
						t_color base_color)
{
	const t_color	color = {
		.r = (int)round((double)base_color.r * x / limit),
		.g = (int)round((double)base_color.g * x / limit),
		.b = (int)round((double)base_color.b * x / limit),
	};

	return (rgb_to_uint(color));
}

static unsigned int	get_lighter_color(double x, double limit, double start,
						t_color base_color)
{
	const t_color	color = {
		.r = (int)round((double)base_color.r
			+ (255.0 - (double)base_color.r) * (x - start) / (limit - start)),
		.g = (int)round((double)base_color.g
			+ (255.0 - (double)base_color.g) * (x - start) / (limit - start)),
		.b = (int)round((double)base_color.b
			+ (255.0 - (double)base_color.b) * (x - start) / (limit - start)),
	};

	return (rgb_to_uint(color));
}
