/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_mesh_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:25:19 by vfries            #+#    #+#             */
/*   Updated: 2023/09/01 18:25:20 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gui/box.h"
#include "gui/optional_boxes.h"
#include "hooks.h"
#include "gui/UI.h"
#include "font/render.h"
#include "path.h"

static void	update_object_boxes(t_engine *engine, char ***files,
				t_gui_boxes *boxes, const char *path);
static void	create_mesh_boxes(t_engine *engine, t_gui_boxes *boxes,
				char **files);
static void	create_mesh_box(t_engine *engine, t_gui_box *box, char *file);

void	load_mesh_objects(t_engine *engine)
{
	t_mesh_objects	*mesh_objects;

	mesh_objects = &engine->gui.mesh_objects;
	update_object_boxes(engine, &mesh_objects->mesh_files,
		&mesh_objects->mesh_boxes, OBJECTS_PATH);
	mesh_objects->last_update = ft_get_current_time();
}

void	reload_mesh_objects(t_engine *engine)
{
	t_mesh_objects	*mesh_objects;

	mesh_objects = &engine->gui.mesh_objects;
	if (ft_get_time_elapsed_in_seconds(mesh_objects->last_update)
		< TIME_BEFORE_UPDATING_FILES_SECONDS)
		return ;
	load_mesh_objects(engine);
}

static void	update_object_boxes(t_engine *engine, char ***files,
				t_gui_boxes *boxes, const char *path)
{
	char	**new_files;

	new_files = ft_get_files_in_directory(path, ".obj", true);
	if (new_files == NULL)
	{
		ft_print_error("Warning: Failed to get files in directory: ");
		ft_print_error(path);
		ft_print_error("\n");
		return ;
	}
	if (ft_strs_are_equal(new_files, *files))
	{
		ft_free_split(new_files);
		return ;
	}
	ft_free_split(*files);
	create_mesh_boxes(engine, boxes, new_files);
	*files = new_files;
}

static void	create_mesh_boxes(t_engine *engine, t_gui_boxes *boxes,
				char **files)
{
	size_t	i;

	destroy_t_gui_boxes(&engine->window, boxes);
	boxes->size = ft_split_len(files);
	if (boxes->size == 0)
		return ;
	boxes->data = ft_calloc(boxes->size, sizeof(*boxes->data));
	if (boxes->data == NULL)
		ft_fatal_error("Failed to allocate memory for object boxes");
	i = -1;
	while (++i < boxes->size)
		create_mesh_box(engine, &boxes->data[i], files[i]);
}

static void	create_mesh_box(t_engine *engine, t_gui_box *box, char *file)
{
	t_gui_box	*parent;
	char		*dot_address;

	parent = engine->gui.mesh_objects.selection_box;
	*box = create_t_gui_box(engine, (t_gui_box_create){parent, \
			{MESH_BOX_OFFSET, 0}, \
			{parent->size.x - MESH_BOX_OFFSET * 2,
			get_normal_box_size(\
				engine->gui.object_attributes_modification_box)},
			true});
	file = ft_strrchr(file, '/') + 1;
	dot_address = ft_strrchr(file, '.');
	*dot_address = '\0';
	change_image_color(&box->image, SUB_GUI_COLOR);
	write_centered_string_to_image(&engine->gui.font, &box->image, file);
	round_image_corners(&box->image, BOX_ROUNDING_RADIUS);
	init_image(&box->on_hover_image, &engine->window, box->size.x, box->size.y);
	change_image_color(&box->on_hover_image, HOVER_GUI_COLOR);
	write_centered_string_to_image(&engine->gui.font, &box->on_hover_image,
		file);
	round_image_corners(&box->on_hover_image, BOX_ROUNDING_RADIUS);
	*dot_address = '.';
	box->draw = NULL;
	box->on_click = NULL;
}
