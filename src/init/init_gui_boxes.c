#include <stdlib.h>
#include <errno.h>

#include "libft.h"

#include "struct/t_minirt.h"
#include "struct/t_gui_box.h"
#include "struct/t_window.h"
#include "init.h"

static int	init_object_creation_gui_box(t_minirt *minirt,
				t_gui_box *gui_box);

int init_gui_boxes(t_minirt *minirt)
{
	minirt->gui_boxes.size = 1;
	minirt->gui_boxes.gui_boxes = malloc(sizeof(t_gui_box));
	if (minirt->gui_boxes.gui_boxes == NULL)
		return (-1);
	if (init_object_creation_gui_box(minirt,
			minirt->gui_boxes.gui_boxes) < 0)
	{
		free(minirt->gui_boxes.gui_boxes);
		return (-1);
	}
	return (0);
}
#include "colors.h"
static void	on_click_test(t_gui_box *self, t_minirt *minirt);
static int	init_object_creation_gui_box(t_minirt *minirt,
										   t_gui_box *gui_box)
{
	*gui_box = create_t_gui_box(minirt, NULL,
								(t_point_int_2d){.x = 0, .y = 4},
								(t_size_int_2d){.width = WINDOW_WIDTH,
										   .height = WINDOW_HEIGHT / 10});
	if (errno == EINVAL)
		return (-1);
	for (int i = 0; i < WINDOW_WIDTH; i++)
		for (int j = 0; j < WINDOW_HEIGHT / 10; j++)
			put_pixel_on_img(&gui_box->image, j, i, COLOR_WHITE);
	gui_box->children.size = 1;
	gui_box->children.gui_boxes = malloc(sizeof(t_gui_box));
	if (gui_box->children.gui_boxes == NULL)
		return (-1); // TODO secure me free image
	*gui_box->children.gui_boxes = create_t_gui_box(minirt, gui_box,
			(t_point_int_2d){.x = gui_box->size.width / 2 - 20, .y = gui_box->size.height / 2 - 20},
			(t_size_int_2d){.width = 40, .height = 40});
	for (int i = 0; i < gui_box->children.gui_boxes->size.width; i++)
		for (int j = 0; j < gui_box->children.gui_boxes->size.height; j++)
			put_pixel_on_img(&gui_box->children.gui_boxes->image, j, i, COLOR_BLUE);
	gui_box->children.gui_boxes->on_click = (void (*)(t_gui_box*, void*))&on_click_test;
	return (0);
}

static void	on_click_test(t_gui_box *self, t_minirt *minirt)
{
	unsigned int color;
	char	*dst;

	dst = self->image.address
		  + (0 * self->image.line_length + 0 * (self->image.bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	if (color == COLOR_BLUE)
		for (int i = 0; i < self->size.width; i++)
			for (int j = 0; j < self->size.height; j++)
				put_pixel_on_img(&self->image, j, i, COLOR_SAND);
	else
		for (int i = 0; i < self->size.width; i++)
			for (int j = 0; j < self->size.height; j++)
				put_pixel_on_img(&self->image, j, i, COLOR_BLUE);
	(void) minirt;
}
