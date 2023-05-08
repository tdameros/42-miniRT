#include <stdlib.h>
#include <errno.h>
#include <math.h>

#include "libft.h"

#include "struct/t_minirt.h"
#include "struct/t_gui_box.h"
#include "colors.h"
#include "init.h"

#define CIRCLE_COLOR 0x00666666

static void	write_setting_icon(t_image *image, unsigned int color);
static void	draw_circle(t_image *image, t_point_int_2d circle_center,
				int radius, unsigned int color);

void	init_settings_icon(t_gui_box *gui_box)
{
	write_setting_icon(&gui_box->image, COLOR_TRANSPARENT);
	write_setting_icon(&gui_box->on_hover_image, ICON_BOX_COLOR);
	round_image_corners(&gui_box->on_hover_image, ICON_BOX_ROUNDING_RADIUS);
}

static void	write_setting_icon(t_image *image, const unsigned int color)
{
	const int circle_diameter
			= (int) ((double) ft_get_smallest_int(image->width, image->height) * 0.65);

	change_image_color(image, color);
	draw_circle(image, (t_point_int_2d) {
						.x = image->width / 2,
						.y = image->height / 2},
				circle_diameter / 2, CIRCLE_COLOR);
	draw_circle(image, (t_point_int_2d) {
						.x = image->width / 2,
						.y = image->height / 2 - circle_diameter / 2.5},
				circle_diameter / 4, CIRCLE_COLOR);

	draw_circle(image, (t_point_int_2d) {
						.x = image->width / 2 - circle_diameter / M_PI,
						.y = image->height / 2 - circle_diameter / M_PI + circle_diameter / 7},
				circle_diameter / 4, CIRCLE_COLOR);
	draw_circle(image, (t_point_int_2d) {
						.x = image->width / 2 + circle_diameter / M_PI,
						.y = image->height / 2 - circle_diameter / M_PI + circle_diameter / 7},
				circle_diameter / 4, CIRCLE_COLOR);

	draw_circle(image, (t_point_int_2d) {
						.x = image->width / 2,
						.y = image->height / 2 + circle_diameter / 2.5},
				circle_diameter / 4, CIRCLE_COLOR);

	draw_circle(image, (t_point_int_2d) {
						.x = image->width / 2 - circle_diameter / M_PI,
						.y = image->height / 2 + circle_diameter / M_PI - circle_diameter / 7},
				circle_diameter / 4, CIRCLE_COLOR);
	draw_circle(image, (t_point_int_2d) {
						.x = image->width / 2 + circle_diameter / M_PI,
						.y = image->height / 2 + circle_diameter / M_PI - circle_diameter / 7},
				circle_diameter / 4, CIRCLE_COLOR);

	draw_circle(image, (t_point_int_2d) {
						.x = image->width / 2,
						.y = image->height / 2},
				circle_diameter / 2.5, color);
}

static void	draw_circle(t_image *image, t_point_int_2d circle_center,
						   int radius, unsigned int color)
{
	const double	radius_squared = radius * radius;
	int				y;
	int				x;

	y = -1;
	while (++y < image->height)
	{
		x = -1;
		while (++x < image->width)
			if (pow(x - circle_center.x, 2) + pow(y - circle_center.y, 2)
				<= radius_squared)
				put_pixel_on_image(image, y, x, color);
	}
}
