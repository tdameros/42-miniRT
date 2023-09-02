/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_selection_boxes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:42:25 by vfries            #+#    #+#             */
/*   Updated: 2023/09/01 18:42:26 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gui/optional_boxes.h"

static void	get_paths_to_ppm_files(t_engine *engine);
static void	remove_name_of_executable(char *path);

void	init_selection_boxes(t_engine *engine, t_gui_box *gui_box)
{
	get_paths_to_ppm_files(engine);
	init_image(&gui_box->image, &engine->window, gui_box->size.x,
		gui_box->size.y);
	gui_box->draw = &textures_and_normal_maps_draw;
	gui_box->on_click = &textures_and_normal_maps_on_click;
	engine->gui.color_and_material.textures_and_normal_maps.selection_box
		= gui_box;
	load_textures_and_normal_maps(engine);
}

static void	get_paths_to_ppm_files(t_engine *engine)
{
	t_textures_and_normal_maps	*textures_and_normal_maps;
	char						*path_to_executable;

	path_to_executable = realpath(engine->argv[0], NULL);
	if (path_to_executable == NULL)
		ft_fatal_error("Failed to get path to executable");
	remove_name_of_executable(path_to_executable);
	textures_and_normal_maps
		= &engine->gui.color_and_material.textures_and_normal_maps;
	textures_and_normal_maps->path_to_textures_folder
		= ft_strjoin(path_to_executable, "/assets/textures");
	textures_and_normal_maps->path_to_normal_maps_folder
		= ft_strjoin(path_to_executable, "/assets/normal_maps");
	free(path_to_executable);
	if (textures_and_normal_maps->path_to_textures_folder == NULL
		|| textures_and_normal_maps->path_to_normal_maps_folder == NULL)
		ft_fatal_error("Failed to get path to textures and normal maps");
}

static void	remove_name_of_executable(char *path)
{
	char	*cursor;

	cursor = path + ft_strlen(path);
	if (*cursor == '/')
		*cursor-- = '\0';
	while (cursor >= path && *cursor != '/')
		cursor--;
	if (cursor > path)
		*cursor = '\0';
}
