#include <stddef.h>
#include <errno.h>

#include "libft.h"

#include "gui/box.h"
#include "window.h"
#include "engine.h"

struct s_limit
{
	int	left;
	int	right;
	int	top;
	int	bottom;
};

static bool	can_gui_box_be_placed(t_gui_boxes main_gui_boxes,
				const t_gui_box *parent, t_vector2i position,
				t_vector2i size);
static bool	is_gui_box_too_big_to_fit_in_parent(t_vector2i parent_size,
				t_vector2i position, t_vector2i size);
static bool	does_gui_box_overlap_with_another_on_the_same_level(
				t_gui_boxes same_level_gui_boxes,
				t_vector2i position, t_vector2i size);
static bool	do_gui_boxes_overlap(struct s_limit new_gui_box_limit,
				const t_gui_box *gui_box_to_compare);

t_gui_box	create_t_gui_box(t_engine *minirt,
				t_gui_box *parent, const t_vector2i position,
				const t_vector2i size)
{
	t_gui_box	gui_box;

	errno = 0;
	ft_bzero(&gui_box, sizeof(gui_box));
	if (can_gui_box_be_placed(minirt->gui.gui_boxes, parent, position,
			size) == false)
	{
		errno = EINVAL;
		return (gui_box);
	}
	init_image(&gui_box.image, &minirt->window, size.x, size.y);
	if (gui_box.image.data == NULL)
	{
		ft_bzero(&gui_box, sizeof(gui_box));
		errno = ENOMEM;
	}
	gui_box.parent = parent;
	gui_box.position = position;
	gui_box.size = size;
	gui_box.draw = &default_gui_box_draw;
	gui_box.on_click = &default_gui_box_on_click;
	return (gui_box);
}

static bool	can_gui_box_be_placed(t_gui_boxes main_gui_boxes,
				const t_gui_box *parent, t_vector2i position,
				t_vector2i size)
{
	t_gui_boxes	same_level_gui_boxes;
	t_vector2i	parent_size;

	if (parent != NULL)
	{
		same_level_gui_boxes = parent->children;
		parent_size = parent->size;
	}
	else
	{
		same_level_gui_boxes = main_gui_boxes;
		parent_size = (t_vector2i){.x = WINDOW_WIDTH,
			.y = WINDOW_HEIGHT};
	}
	return (
		!(is_gui_box_too_big_to_fit_in_parent(parent_size, position, size)
			|| does_gui_box_overlap_with_another_on_the_same_level(
				same_level_gui_boxes, position, size)));
}

static bool	is_gui_box_too_big_to_fit_in_parent(
		t_vector2i parent_size, t_vector2i position,
		t_vector2i size)
{
	return (position.y + size.y > parent_size.y
		|| position.x + size.x > parent_size.x);
}

static bool	does_gui_box_overlap_with_another_on_the_same_level(
		t_gui_boxes same_level_gui_boxes,
		t_vector2i position, t_vector2i size)
{
	size_t					i;
	const struct s_limit	new_gui_box_limit = {
		.left = position.x,
		.right = position.x + size.x,
		.top = position.y,
		.bottom = position.y + size.y
	};

	i = same_level_gui_boxes.size;
	while (i--)
		if (do_gui_boxes_overlap(new_gui_box_limit,
				same_level_gui_boxes.data + i))
			return (true);
	return (false);
}

static bool	do_gui_boxes_overlap(struct s_limit new_gui_box_limit,
									const t_gui_box *gui_box_to_compare)
{
	const struct s_limit	gui_box_to_compare_limit = {
		.left = gui_box_to_compare->position.x,
		.right = gui_box_to_compare->position.x \
			+ gui_box_to_compare->size.x,
		.top = gui_box_to_compare->position.y,
		.bottom = gui_box_to_compare->position.y \
			+ gui_box_to_compare->size.y
	};

	return ((new_gui_box_limit.bottom > gui_box_to_compare_limit.top
			|| new_gui_box_limit.top < gui_box_to_compare_limit.bottom
			|| new_gui_box_limit.left > gui_box_to_compare_limit.right
			|| new_gui_box_limit.right < gui_box_to_compare_limit.left)
		== false);
}
