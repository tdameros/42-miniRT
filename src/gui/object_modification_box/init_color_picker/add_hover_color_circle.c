#include <math.h>

#include "gui/box.h"
#include "colors.h"
#include "gui/utils.h"

static void	put_colored_circle(t_image *on_hover_image,
				t_vector2i mouse_position, unsigned int color,
				t_image *base_image);

void	add_hover_color_circle(t_gui_box *self, const t_vector2i offset,
			t_vector2i mouse_position)
{
	unsigned int		color;

	mouse_position = get_mouse_position_in_box(self, offset,
			mouse_position);
	color = get_image_pixel_color(&self->image, mouse_position.y,
			mouse_position.x);
	put_colored_circle(&self->on_hover_image, mouse_position, color,
		&self->image);
}

static void	put_colored_circle(t_image *on_hover_image,
				t_vector2i mouse_position, unsigned int color,
				t_image *base_image)
{
	const float	radius_squared = powf(10.f, 2.f);
	int			y;
	int			x;
	float		equation_result;

	y = on_hover_image->height;
	while (y--)
	{
		x = on_hover_image->width;
		while (x--)
		{
			if (get_image_pixel_color(base_image, y, x) == COLOR_TRANSPARENT)
				continue ;
			equation_result = powf(x - mouse_position.x, 2.f)
				+ powf(y - mouse_position.y, 2.f);
			if (equation_result > radius_squared - 10.f
				&& equation_result < radius_squared + 10.f)
				put_pixel_on_image(on_hover_image, y, x, COLOR_BLACK);
			else if (equation_result < radius_squared)
				put_pixel_on_image(on_hover_image, y, x, color);
			else
				put_pixel_on_image(on_hover_image, y, x, COLOR_TRANSPARENT);
		}
	}
}
