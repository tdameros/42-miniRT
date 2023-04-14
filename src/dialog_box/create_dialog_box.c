#include <stddef.h>
#include <errno.h>

#include "libft.h"

#include "struct/t_dialog_box.h"
#include "struct/window.h"
#include "struct/t_minirt.h"
#include "miniRT.h"

struct s_limit
{
	int	left;
	int	right;
	int	top;
	int	bottom;
};

static bool	can_dialog_box_be_placed(t_dialog_boxes main_dialog_boxes,
				const t_dialog_box *parent, t_point_int_2d position,
				t_size_int_2d size);
static bool	is_dialog_box_too_big_to_fit_in_parent(t_size_int_2d parent_size,
				t_point_int_2d position, t_size_int_2d size);
static bool	does_dialog_box_overlap_with_another_on_the_same_level(
				t_dialog_boxes same_level_dialog_boxes,
				t_point_int_2d position, t_size_int_2d size);
static bool	do_dialog_boxes_overlap(struct s_limit new_dialog_box_limit,
				const t_dialog_box *dialog_box_to_compare);

t_dialog_box	create_t_dialog_box(t_minirt *minirt,
					t_dialog_box *parent, const t_point_int_2d position,
					const t_size_int_2d size)
{
	t_dialog_box	dialog_box;

	errno = 0;
	ft_bzero(&dialog_box, sizeof(t_dialog_box));
	if (can_dialog_box_be_placed(minirt->dialog_boxes, parent, position,
			size) == false)
	{
		errno = EINVAL;
		return (dialog_box);
	}
	dialog_box.parent = parent;
	dialog_box.position = position;
	dialog_box.size = size;
	init_image(&dialog_box.image, &minirt->window, size.height, size.width);
	return (dialog_box);
}

static bool	can_dialog_box_be_placed(const t_dialog_boxes main_dialog_boxes,
				const t_dialog_box *parent, const t_point_int_2d position,
				const t_size_int_2d size)
{
	t_dialog_boxes	same_level_dialog_boxes;
	t_size_int_2d	parent_size;

	if (parent != NULL)
	{
		same_level_dialog_boxes = parent->children;
		parent_size = parent->size;
	}
	else
	{
		same_level_dialog_boxes = main_dialog_boxes;
		parent_size = create_t_size_int_2d(WINDOW_WIDTH, WINDOW_HEIGHT);
	}
	return (
		(
			is_dialog_box_too_big_to_fit_in_parent(parent_size, position, size)
			|| does_dialog_box_overlap_with_another_on_the_same_level(
				same_level_dialog_boxes, position, size)
		) == false);
}

static bool	is_dialog_box_too_big_to_fit_in_parent(
				const t_size_int_2d parent_size, const t_point_int_2d position,
				const t_size_int_2d size)
{
	return (position.y + size.height >= parent_size.height
		|| position.x + size.width >= parent_size.width);
}

static bool	does_dialog_box_overlap_with_another_on_the_same_level(
				const t_dialog_boxes same_level_dialog_boxes,
				const t_point_int_2d position, const t_size_int_2d size)
{
	size_t					i;
	const struct s_limit	new_dialog_box_limit = {
		.left = position.x,
		.right = position.x + size.width,
		.top = position.y,
		.bottom = position.y + size.height
	};

	i = same_level_dialog_boxes.size;
	while (i--)
		if (do_dialog_boxes_overlap(new_dialog_box_limit,
				&same_level_dialog_boxes.dialog_boxes[i]))
			return (true);
	return (false);
}

static bool	do_dialog_boxes_overlap(const struct s_limit new_dialog_box_limit,
				const t_dialog_box *dialog_box_to_compare)
{
	const struct s_limit	dialog_box_to_compare_limit = {
		.left = dialog_box_to_compare->position.x,
		.right = dialog_box_to_compare->position.x \
			+ dialog_box_to_compare->size.width,
		.top = dialog_box_to_compare->position.y,
		.bottom = dialog_box_to_compare->position.y \
			+ dialog_box_to_compare->size.height
	};

	return (new_dialog_box_limit.bottom > dialog_box_to_compare_limit.top
		|| new_dialog_box_limit.top < dialog_box_to_compare_limit.bottom
		|| new_dialog_box_limit.left > dialog_box_to_compare_limit.right
		|| new_dialog_box_limit.right < dialog_box_to_compare_limit.left);
}
