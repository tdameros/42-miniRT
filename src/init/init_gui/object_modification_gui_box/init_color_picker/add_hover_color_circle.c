#include <math.h>

#include "struct/t_gui_box.h"
#include "init.h"
#include "colors.h"

static void	put_colored_circle(t_image *image, t_point_int_2d mouse_position,
				unsigned int color);

void	add_hover_color_circle(t_gui_box *self, t_minirt *minirt,
			int x_offset, int y_offset)
{
	const t_point_int_2d	mouse_position = get_mouse_position(self, minirt,
			x_offset, y_offset);
	unsigned int			color;

	if (mouse_is_hovering_box(self, mouse_position) == false)
		return ;
	color = get_image_pixel_color(&self->image, mouse_position.y,
			mouse_position.x);
	put_colored_circle(&self->image, mouse_position, color);
}

static void	put_colored_circle(t_image *image, t_point_int_2d mouse_position,
				unsigned int color)
{
	const double	radius_squared = pow(10, 2);
	int				y;
	int				x;
	double			equation_result;

	y = -1;
	while (++y < image->height)
	{
		x = -1;
		while (++x < image->width)
		{
			if (get_image_pixel_color(image, y, x) == COLOR_TRANSPARENT)
				continue ;
			equation_result = pow(x - mouse_position.x, 2)
				+ pow(y - mouse_position.y, 2);
			if (equation_result > radius_squared - 10
				&& equation_result < radius_squared + 10)
				put_pixel_on_image(image, y, x, COLOR_BLACK);
			else if (equation_result < radius_squared)
				put_pixel_on_image(image, y, x, color);
		}
	}
}
