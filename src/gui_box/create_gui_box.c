#include <stddef.h>
#include <errno.h>

#include "libft.h"

#include "struct/t_gui_box.h"
#include "struct/t_window.h"
#include "struct/t_minirt.h"

struct s_limit
{
	int	left;
	int	right;
	int	top;
	int	bottom;
};

static bool	can_gui_box_be_placed(t_gui_boxes main_gui_boxes,
				const t_gui_box *parent, t_point_int_2d position,
				t_size_int_2d size);
static bool	is_gui_box_too_big_to_fit_in_parent(t_size_int_2d parent_size,
				t_point_int_2d position, t_size_int_2d size);
static bool	does_gui_box_overlap_with_another_on_the_same_level(
				t_gui_boxes same_level_gui_boxes,
				t_point_int_2d position, t_size_int_2d size);
static bool	do_gui_boxes_overlap(struct s_limit new_gui_box_limit,
				const t_gui_box *gui_box_to_compare);

t_gui_box	create_t_gui_box(t_minirt *minirt,
							  t_gui_box *parent, const t_point_int_2d position,
							  const t_size_int_2d size)
{
	t_gui_box	gui_box;

	errno = 0;
	ft_bzero(&gui_box, sizeof(gui_box));
	if (can_gui_box_be_placed(minirt->gui_boxes, parent, position,
							  size) == false)
	{
		errno = EINVAL;
		return (gui_box);
	}
	gui_box.parent = parent;
	gui_box.position = position;
	gui_box.size = size;
	init_image(&gui_box.image, &minirt->window, size.height, size.width); // TODO can this fail?
	return (gui_box);
}

static bool	can_gui_box_be_placed(t_gui_boxes main_gui_boxes,
				const t_gui_box *parent, t_point_int_2d position,
				t_size_int_2d size)
{
	t_gui_boxes	same_level_gui_boxes;
	t_size_int_2d	parent_size;

	if (parent != NULL)
	{
		same_level_gui_boxes = parent->children;
		parent_size = parent->size;
	}
	else
	{
		same_level_gui_boxes = main_gui_boxes;
		parent_size = (t_size_int_2d){.width = WINDOW_WIDTH,
				.height = WINDOW_HEIGHT};
	}
	return (!
		(is_gui_box_too_big_to_fit_in_parent(parent_size, position, size)
		 || does_gui_box_overlap_with_another_on_the_same_level(
				same_level_gui_boxes, position, size)));
}

static bool	is_gui_box_too_big_to_fit_in_parent(
				t_size_int_2d parent_size, t_point_int_2d position,
				t_size_int_2d size)
{
	return (position.y + size.height > parent_size.height
		|| position.x + size.width > parent_size.width);
}

static bool	does_gui_box_overlap_with_another_on_the_same_level(
				t_gui_boxes same_level_gui_boxes,
				t_point_int_2d position, t_size_int_2d size)
{
	size_t					i;
	const struct s_limit	new_gui_box_limit = {
		.left = position.x,
		.right = position.x + size.width,
		.top = position.y,
		.bottom = position.y + size.height
	};

	i = same_level_gui_boxes.size;
	while (i--)
		if (do_gui_boxes_overlap(new_gui_box_limit,
								 same_level_gui_boxes.gui_boxes + i))
			return (true);
	return (false);
}

static bool	do_gui_boxes_overlap(struct s_limit new_gui_box_limit,
									const t_gui_box *gui_box_to_compare)
{
	const struct s_limit	gui_box_to_compare_limit = {
		.left = gui_box_to_compare->position.x,
		.right = gui_box_to_compare->position.x \
			+ gui_box_to_compare->size.width,
		.top = gui_box_to_compare->position.y,
		.bottom = gui_box_to_compare->position.y \
			+ gui_box_to_compare->size.height
	};

	return ((new_gui_box_limit.bottom > gui_box_to_compare_limit.top
			 || new_gui_box_limit.top < gui_box_to_compare_limit.bottom
			 || new_gui_box_limit.left > gui_box_to_compare_limit.right
			 || new_gui_box_limit.right < gui_box_to_compare_limit.left)
		== false);
}
