#include <sys/errno.h>
#include <stdlib.h>
#include "colors.h"
#include "struct/t_gui_box.h"
#include "init.h"

static void	on_click_test(t_gui_box *self, t_minirt *minirt, int y, int x);

int	init_object_creation_gui_box(t_minirt *minirt, t_gui_box *gui_box)
{
	*gui_box = create_t_gui_box(minirt, NULL,
			(t_point_int_2d){.x = 12, \
							 .y = 12},
			(t_size_int_2d){.width = WINDOW_WIDTH - 24, \
							.height = WINDOW_HEIGHT / 8});
	if (errno == EINVAL)
		return (-1);
	change_image_color(&gui_box->image, 0x40000000);
	round_image_corners(&gui_box->image, 20);
	gui_box->draw = &default_gui_box_draw;
	gui_box->children.size = 1;
	gui_box->children.gui_boxes = malloc(sizeof(*gui_box->children.gui_boxes)
										 * gui_box->children.size);
	if (gui_box->children.gui_boxes == NULL)
		return (-1); // TODO destroy previous gui_box
	*gui_box->children.gui_boxes = create_t_gui_box(minirt, gui_box,
			(t_point_int_2d){.x = gui_box->size.width / 2 - 20, \
							 .y = gui_box->size.height / 2 - 20},
			(t_size_int_2d){.width = 40, .height = 40});
	if (errno == EINVAL)
		return (-1); // TODO destroy previous gui_box
	change_image_color(&gui_box->children.gui_boxes->image, COLOR_BLUE);
	round_image_corners(&gui_box->children.gui_boxes->image, 20);
	gui_box->children.gui_boxes->draw = &default_gui_box_draw;
	gui_box->children.gui_boxes->on_click = &on_click_test;
	return (0);
}

static void	on_click_test(t_gui_box *self, t_minirt *minirt, int y, int x)
{
	unsigned int color;

	color = get_image_pixel_color(&self->image, y, x);
	if (color == COLOR_BLUE)
	{
		change_image_color(&self->image, COLOR_SAND);
		round_image_corners(&self->image, 20);
	}
	else if (color != COLOR_TRANSPARENT)
	{
		change_image_color(&self->image, COLOR_BLUE);
		round_image_corners(&self->image, 20);
	}
	(void) minirt;
}
