#include <stdlib.h>
#include <errno.h>

#include "libft.h"

#include "struct/t_minirt.h"
#include "struct/t_gui_box.h"
#include "struct/t_window.h"
#include "init.h"

static int	init_object_creation_dialog_box(t_minirt *minirt,
											  t_gui_box *dialog_box);

int init_dialog_boxes(t_minirt *minirt)
{
	minirt->dialog_boxes.size = 1;
	minirt->dialog_boxes.dialog_boxes = malloc(sizeof(t_gui_box));
	if (minirt->dialog_boxes.dialog_boxes == NULL)
		return (-1);
	if (init_object_creation_dialog_box(minirt,
			minirt->dialog_boxes.dialog_boxes) < 0)
	{
		free(minirt->dialog_boxes.dialog_boxes);
		return (-1);
	}
	return (0);
}

static int	init_object_creation_dialog_box(t_minirt *minirt,
											  t_gui_box *dialog_box)
{
	*dialog_box = create_t_dialog_box(minirt, NULL,
			(t_point_int_2d){.x = 0, .y = 10},
			(t_size_int_2d){.width = WINDOW_WIDTH,
				.height = WINDOW_HEIGHT / 10});
	if (errno == EINVAL)
		return (-1);
	for (int i = 0; i < WINDOW_WIDTH; i++)
		for (int j = 0; j < WINDOW_HEIGHT / 10; j++)
			put_pixel_on_img(&dialog_box->image, j, i, 0xFFFFFF);
	return (0);
}
