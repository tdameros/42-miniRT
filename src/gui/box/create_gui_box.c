/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_gui_box.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:22:23 by vfries            #+#    #+#             */
/*   Updated: 2023/09/23 22:38:01 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <errno.h>

#include "libft.h"

#include "gui/box.h"
#include "window.h"
#include "engine.h"

static bool	can_gui_box_be_placed(const t_engine *engine,
				const t_gui_box *parent, t_vector2i position, t_vector2i size);
static bool	is_gui_box_too_big_to_fit_in_parent(t_vector2i parent_size,
				t_vector2i position, t_vector2i size);
static bool	does_gui_box_overlap_with_another_on_the_same_level(
				t_gui_boxes same_level_gui_boxes,
				t_vector2i position, t_vector2i size);
static bool	do_gui_boxes_overlap(struct s_limit new_gui_box_limit,
				const t_gui_box *gui_box_to_compare);

t_gui_box	create_t_gui_box(t_engine *engine, t_gui_box_create args)
{
	t_gui_box	gui_box;

	errno = 0;
	ft_bzero(&gui_box, sizeof(gui_box));
	if (can_gui_box_be_placed(engine, args.parent, args.position, args.size)
		== false)
		ft_fatal_error("Failed to create gui box, is out of bounds");
	if (args.should_create_an_image)
		init_image(&gui_box.image, &engine->window, args.size.x, args.size.y);
	gui_box.parent = args.parent;
	gui_box.position = args.position;
	gui_box.size = args.size;
	gui_box.draw = &default_gui_box_draw;
	gui_box.on_click = &default_gui_box_on_click;
	gui_box.was_initialised = true;
	return (gui_box);
}

static bool	can_gui_box_be_placed(const t_engine *engine,
				const t_gui_box *parent, t_vector2i position, t_vector2i size)
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
		same_level_gui_boxes = engine->gui.gui_boxes;
		parent_size = engine->window.size;
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
		if (same_level_gui_boxes.data[i].was_initialised
			&& do_gui_boxes_overlap(new_gui_box_limit,
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
