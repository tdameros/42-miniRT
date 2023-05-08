#include <math.h>

#include "libft.h"

#include "struct/t_minirt.h"
#include "struct/t_gui_box.h"
#include "colors.h"
#include "init.h"

#define CIRCLE_COLOR 0x00666666

static void	write_setting_icon(t_image *image, unsigned int color);
static void	draw_circle(t_image *image, t_point_int_2d circle_center,
				float radius, unsigned int color);

void	init_settings_icon(t_gui_box *gui_box)
{
	write_setting_icon(&gui_box->image, COLOR_TRANSPARENT);
	write_setting_icon(&gui_box->on_hover_image, ICON_BOX_COLOR);
	round_image_corners(&gui_box->on_hover_image, ICON_BOX_ROUNDING_RADIUS);
}

static void	write_setting_icon(t_image *image, const unsigned int color)
{
	const float	circle_diameter
		= ft_get_smallest_int(image->width, image->height)
		* 0.65f;
	const float	circle_radius = circle_diameter / 2.f;
	float		theta;

	change_image_color(image, color);
	draw_circle(image, (t_point_int_2d){
		.x = image->width / 2,
		.y = image->height / 2},
		circle_radius, CIRCLE_COLOR);
	theta = M_PI / 2.f;
	while (theta < M_PI * 2.f + M_PI / 2.f)
	{
		draw_circle(image, (t_point_int_2d){
			.x = image->width / 2.f + circle_radius * cosf(theta),
			.y = image->height / 2.f + circle_radius * sinf(theta)},
			circle_radius * 0.42f, CIRCLE_COLOR);
		theta += M_PI * 2.f / 6.f;
	}
	draw_circle(image, (t_point_int_2d){
		.x = image->width / 2,
		.y = image->height / 2},
		circle_diameter / 2.4f, color);
}

static void	draw_circle(t_image *image, t_point_int_2d circle_center,
				float radius, unsigned int color)
{
	const float	radius_squared = radius * radius;
	int			y_offset;
	int			y;
	int			x;

	y_offset = 0;
	y = -1;
	while (++y < image->height)
	{
		x = -1;
		while (++x < image->width)
			if (powf(x - circle_center.x, 2.f) + powf(y - circle_center.y, 2.f)
				<= radius_squared)
				image->address[y_offset + x] = color;
		y_offset += image->line_length;
	}
}
