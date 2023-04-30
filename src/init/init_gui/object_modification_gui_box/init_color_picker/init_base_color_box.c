/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_base_color_box.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 01:50:32 by vfries            #+#    #+#             */
/*   Updated: 2023/04/28 01:52:39 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "struct/t_minirt.h"
#include "struct/t_gui_box.h"
#include "init.h"
#include "colors.h"

typedef struct s_color_getter
{
	int	red;
	int	(*get_red)(double color, double x, double decal, double ratio);
	int	green;
	int	(*get_green)(double color, double x, double decal, double ratio);
	int	blue;
	int	(*get_blue)(double color, double x, double decal, double ratio);
}	t_color_getter;

typedef struct s_color_separator
{
	int	color_segment_width;
	int	max;
	int	previous_max;
}	t_color_separator;

static void	base_color_box_draw(t_gui_box *self, t_minirt *minirt,
				int x_offset, int y_offset);
static void	put_color_segment(t_image *image, t_point_int_2d *position,
				t_color_separator *color_separator,
				t_color_getter color_getter);
static void	init_color_getters(t_color_getter *color_getters);
static void	write_color_row(t_image *image, int y);
static void	base_color_picker_on_click(t_gui_box *self, t_minirt *minirt, int y,
				int x);

#include "mlx.h"


int	init_base_color_box(t_minirt *minirt, t_gui_box *gui_box,
				t_gui_box *parent)
{
	*gui_box = create_t_gui_box(minirt, parent, \
		(t_point_int_2d){.x = 0,
			.y = parent->size.height - parent->size.height / 2 + 4}, \
		(t_size_int_2d){.height = parent->size.height / 2 - 4, \
			.width = parent->size.width});
	if (errno == EINVAL)
		return (-1);
	gui_box->draw = &base_color_box_draw;
	gui_box->on_click = &base_color_picker_on_click;
	minirt->gui.color_picker_base_color = get_t_color_from_uint(COLOR_BLUE);
	return (0);
}

static void	base_color_box_draw(t_gui_box *self, t_minirt *minirt,
				int x_offset, int y_offset)
{
	int	y;

	y = -1;
	while (++y < self->size.height)
		write_color_row(&self->image, y);
	round_image_corners(&self->image, 10);
	add_hover_color_circle(self, minirt, x_offset, y_offset);
	mlx_put_image_to_window(minirt->window.mlx, minirt->window.window,
		self->image.data,
		self->position.x + x_offset,
		self->position.y + y_offset);
}

static void	write_color_row(t_image *image, int y)
{
	t_color_separator	color_separator;
	t_point_int_2d		position;
	t_color_getter		color_getters[6];

	init_color_getters(color_getters);
	position = (t_point_int_2d){.x = 0, .y = y};
	color_separator.color_segment_width = image->width / 6;
	color_separator.max = color_separator.color_segment_width;
	color_separator.previous_max = 0;
	put_color_segment(image, &position, &color_separator, color_getters[0]);
	put_color_segment(image, &position, &color_separator, color_getters[1]);
	put_color_segment(image, &position, &color_separator, color_getters[2]);
	put_color_segment(image, &position, &color_separator, color_getters[3]);
	put_color_segment(image, &position, &color_separator, color_getters[4]);
	put_color_segment(image, &position, &color_separator, color_getters[5]);
	while (position.x < image->width)
	{
		put_pixel_on_image(image, y, position.x, rgb_to_uint(\
			(t_color){\
				.r = 255, \
				.g = 0, \
				.b = 0}));
		position.x++;
	}
}

static void	init_color_getters(t_color_getter *color_getters)
{
	color_getters[0] = (t_color_getter){
		255, &get_base_color,
		0, &get_base_color,
		255, &get_increasing_color};
	color_getters[1] = (t_color_getter){
		255, &get_decreasing_color,
		0, &get_base_color,
		255, &get_base_color};
	color_getters[2] = (t_color_getter){
		0, &get_base_color,
		255, &get_increasing_color,
		255, &get_base_color};
	color_getters[3] = (t_color_getter){
		0, &get_base_color,
		255, &get_base_color,
		255, &get_decreasing_color};
	color_getters[4] = (t_color_getter){
		255, &get_increasing_color,
		255, &get_base_color,
		0, &get_base_color};
	color_getters[5] = (t_color_getter){
		255, &get_base_color,
		255, &get_decreasing_color,
		0, &get_base_color};
}

static void	put_color_segment(t_image *image, t_point_int_2d *position,
				t_color_separator *color_separator, t_color_getter color_getter)
{
	while (position->x < color_separator->max)
	{
		put_pixel_on_image(image, position->y, position->x,
			rgb_to_uint((t_color){
				.r = color_getter.get_red(color_getter.red,
					position->x, color_separator->previous_max,
					color_separator->color_segment_width),
				.g = color_getter.get_green(color_getter.green,
					position->x, color_separator->previous_max,
					color_separator->color_segment_width),
				.b = color_getter.get_blue(color_getter.blue,
					position->x, color_separator->previous_max,
					color_separator->color_segment_width)}));
		position->x++;
	}
	color_separator->previous_max = color_separator->max;
	color_separator->max += color_separator->color_segment_width;
}

static void	base_color_picker_on_click(t_gui_box *self, t_minirt *minirt, int y,
				int x)
{
	const unsigned int	color = get_image_pixel_color(&self->image, y, x);

	if (color == COLOR_TRANSPARENT)
		return ;
	minirt->gui.color_picker_base_color = get_t_color_from_uint(color);
}
