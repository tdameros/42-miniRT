#include <stdlib.h>
#include <errno.h>
#include <math.h>

#include "libft.h"

#include "struct/t_minirt.h"
#include "struct/t_gui_box.h"
#include "colors.h"

#define CIRCLE_COLOR 0x00666666

static void	write_setting_icon(t_image *image);
static void	draw_circle(t_image *image, t_point_int_2d circle_center,
				int radius, unsigned int color);

int	init_settings_icon(t_minirt *minirt, t_gui_box *gui_box)
{
	gui_box->children.size = 1;
	gui_box->children.length = 1;
	gui_box->children.data = malloc(sizeof(*gui_box->children.data)
		* gui_box->children.size);
	if (gui_box->children.data == NULL)
		return (-1);
	*gui_box->children.data = create_t_gui_box(minirt, gui_box,
		(t_point_int_2d){
			.x = 0,
			.y = 0
		},
		(t_size_int_2d){
			.width = gui_box->size.width,
			.height = gui_box->size.height
		}
	);
	if (errno == EINVAL)
	{
		free(gui_box->children.data);
		ft_bzero(&gui_box->children, sizeof(gui_box->children));
		return (-1);
	}
	gui_box->children.data->draw = &default_gui_box_draw;
	write_setting_icon(&gui_box->children.data->image);
	return (0);
}

static void	write_setting_icon(t_image *image)
{
	const int circle_diameter
			= (int) ((double) ft_get_smallest_int(image->width, image->height) * 0.65);

	change_image_color(image, COLOR_TRANSPARENT);
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
			.y = image->height / 2 - circle_diameter / M_PI + circle_diameter / 10},
			circle_diameter / 4, CIRCLE_COLOR);
	draw_circle(image, (t_point_int_2d) {
			.x = image->width / 2 + circle_diameter / M_PI,
			.y = image->height / 2 - circle_diameter / M_PI + circle_diameter / 10},
			circle_diameter / 4, CIRCLE_COLOR);

	draw_circle(image, (t_point_int_2d) {
			.x = image->width / 2,
			.y = image->height / 2 + circle_diameter / 2.5},
			circle_diameter / 4, CIRCLE_COLOR);

	draw_circle(image, (t_point_int_2d) {
			.x = image->width / 2 - circle_diameter / M_PI,
			.y = image->height / 2 + circle_diameter / M_PI - circle_diameter / 10},
			circle_diameter / 4, CIRCLE_COLOR);
	draw_circle(image, (t_point_int_2d) {
			.x = image->width / 2 + circle_diameter / M_PI,
			.y = image->height / 2 + circle_diameter / M_PI - circle_diameter / 10},
			circle_diameter / 4, CIRCLE_COLOR);

	draw_circle(image, (t_point_int_2d) {
			.x = image->width / 2,
			.y = image->height / 2},
			circle_diameter / 2.5, COLOR_TRANSPARENT);
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
