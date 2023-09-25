/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optional_boxes.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 03:35:03 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/25 03:35:04 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONAL_BOXES_H
# define OPTIONAL_BOXES_H

# include "engine.h"
# include "box.h"

# define TIME_BEFORE_UPDATING_FILES_SECONDS 4.f

# define MESH_BOX_OFFSET 4

# define TEXTURE_BOX_PPM_OFFSET 4

//	add_mesh_object_box/click_mesh_box.c
void		click_mesh_box(t_engine *engine, size_t index);

//	add_mesh_object_box/init_add_mesh_object_box.c
void		init_add_mesh_object_box(t_engine *engine, t_gui_box *gui_box,
				const t_gui_box *main_gui_box,
				const t_gui_box *object_list_box);

//	add_mesh_object_box/load_mesh_objects.c
void		load_mesh_objects(t_engine *engine);
void		reload_mesh_objects(t_engine *engine);

//	add_mesh_object_box/mesh_object_selection_draw.c
void		mesh_object_selection_draw(t_gui_box *self, t_engine *engine,
				t_draw_data draw_data);

//	add_mesh_object_box/mesh_object_selection_on_click.c
void		mesh_object_selection_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data);

//	settings_box/init_antialiasing_toggle_box.c
void		init_antialiasing_toggle_box(t_engine *engine, t_gui_box *gui_box,
				int *y, t_gui_box *parent);

//	settings_box/init_bounces_per_pixel_box.c
void		init_bounces_per_pixel_box(t_engine *engine, t_gui_box *gui_box,
				int *y, t_gui_box *parent);

//	settings_box/init_cam_fov_box.c
void		init_cam_fov_box(t_engine *engine, t_gui_box *gui_box, int *y,
				t_gui_box *parent);

//	settings_box/init_disable_shadows_box.c
void		init_disable_shadows_box(t_engine *engine, t_gui_box *gui_box,
				int *y, t_gui_box *parent);

//	settings_box/init_max_resolution_reduction.c
void		init_max_resolution_reduction_box(t_engine *engine,
				t_gui_box *gui_box, int *y, t_gui_box *parent);

//	settings_box/init_min_resolution_reduction.c
void		init_min_resolution_reduction_box(t_engine *engine,
				t_gui_box *gui_box, int *y, t_gui_box *parent);

//	settings_box/init_reset_camera_peaking_box.c
void		init_reset_camera_peaking_box(t_engine *engine, t_gui_box *gui_box,
				int *y, t_gui_box *parent);

//	settings_box/init_settings_box.c
void		init_settings_box(t_engine *engine, t_gui_box *gui_box,
				const t_gui_box *main_gui_box,
				const t_gui_box *object_list_box);

//	texture_box/outline_cap_picker/draw.c
void		outline_picker_draw(t_gui_box *self, t_engine *engine,
				t_draw_data draw_data);
void		cap_picker_draw(t_gui_box *self, t_engine *engine,
				t_draw_data draw_data);

//	texture_box/outline_cap_picker/init_outline_cap_picker.c
void		init_outline_cap_picker(t_engine *engine, t_gui_box *gui_box);

//	texture_box/outline_cap_picker/on_click.c
void		outline_picker_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data);
void		cap_picker_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data);

//	texture_box/selection_box/click_ppm_box.c
void		click_ppm_box(t_engine *engine, size_t index);

//	texture_box/selection_box/init_selection_boxes.c
void		init_selection_boxes(t_engine *engine, t_gui_box *gui_box);

//	texture_box/selection_box/load_textures_and_normal_maps.c
void		load_textures_and_normal_maps(t_engine *engine);
void		reload_textures_and_normal_maps(t_engine *engine);

//	texture_box/selection_box/textures_and_normal_maps_draw.c
void		textures_and_normal_maps_draw(t_gui_box *self, t_engine *engine,
				t_draw_data draw_data);

//	texture_box/selection_box/textures_and_normal_maps_on_click.c
void		textures_and_normal_maps_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data);

//	texture_box/texture_normal_map_picker/draw.c
void		texture_picker_draw(t_gui_box *self, t_engine *engine,
				t_draw_data draw_data);
void		normal_map_picker_draw(t_gui_box *self, t_engine *engine,
				t_draw_data draw_data);

//	texture_box/texture_normal_map_picker/init_texture_normal_map_picker.c
void		init_texture_normal_map_picker(t_engine *engine,
				t_gui_box *gui_box);

//	texture_box/texture_normal_map_picker/on_click.c
void		texture_picker_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data);
void		normal_map_picker_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data);

//	texture_box/delete_box.c
void		init_delete_box(t_engine *engine, t_gui_box *delete_box);
void		update_delete_box(t_engine *engine);

//	texture_box/init_texture_box.c
void		init_texture_box(t_engine *engine, t_gui_box *gui_box,
				const t_gui_box *main_gui_box,
				const t_gui_box *object_list_box);

//	add_button_box.c
void		add_button_box(t_engine *engine, t_gui_box *gui_box, int *y,
				t_gui_box *parent);

//	add_plus_minus_box.c
void		add_plus_minus_box(t_engine *engine, t_gui_box *gui_box, int *y,
				t_gui_box *parent);

//	create_optional_box.c
t_gui_box	create_optional_box(t_engine *engine, const t_gui_box *main_gui_box,
				const t_gui_box *object_list_box);

#endif
