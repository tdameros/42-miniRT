#include <math.h>

#include "libft.h"

#include "gui/box.h"
#include "gui/main_gui_box.h"
#include "engine.h"
#include "colors.h"
#include "gui/UI.h"

#define CIRCLE_COLOR 0x00666666

static void	write_setting_icon(t_image *image, unsigned int color);

void	init_settings_icon(t_gui_box *gui_box)
{
	write_setting_icon(&gui_box->image, COLOR_TRANSPARENT);
	write_setting_icon(&gui_box->on_hover_image, HOVER_GUI_COLOR);
	round_image_corners(&gui_box->on_hover_image, BOX_ROUNDING_RADIUS);
}

static void	write_setting_icon(t_image *image, const unsigned int color)
{
	const float	circle_diameter
		= ft_get_smallest_int(image->width, image->height)
		* 0.65f;
	const float	circle_radius = circle_diameter / 2.f;
	float		theta;

	change_image_color(image, color);
	image_draw_circle(image, (t_vector2i) {
							  .x = image->width / 2,
							  .y = image->height / 2},
					  circle_radius, CIRCLE_COLOR);
	theta = M_PI / 2.f;
	while (theta < M_PI * 2.f + M_PI / 2.f)
	{
		image_draw_circle(image, (t_vector2i) {
								  .x = image->width / 2.f + circle_radius * cosf(theta),
								  .y = image->height / 2.f + circle_radius * sinf(theta)},
						  circle_radius * 0.42f, CIRCLE_COLOR);
		theta += M_PI * 2.f / 6.f;
	}
	image_draw_circle(image, (t_vector2i) {
							  .x = image->width / 2,
							  .y = image->height / 2},
					  circle_diameter / 2.4f, color);
}
