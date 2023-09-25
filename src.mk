SRC				=\
	draw/bounding_box.c		\
	draw/draw.c				\
	draw/draw_line.c		\
	draw/mesh_bvh_node.c	\
	draw/objects_bvh_node.c	\
	\
	\
	export/scene/datetime.c	\
	export/scene/material.c	\
	export/scene/object.c	\
	export/scene/objects.c	\
	export/scene/scene.c	\
	export/image_to_ppm.c	\
	export/screenshot.c		\
	\
	font/parsing/get_glyph_offset.c					\
	font/parsing/get_glyph_outlines.c				\
	font/parsing/get_long_hor_metric.c				\
	font/parsing/read_8_bits.c						\
	font/parsing/read_16_bits.c						\
	font/parsing/read_32_bits.c						\
	font/parsing/read_64_bits.c						\
	font/parsing/read_cmap.c						\
	font/parsing/read_font_directory.c				\
	font/parsing/read_format4.c						\
	font/parsing/read_glyph_outline.c				\
	font/parsing/read_glyph_outline_coordinates.c	\
	font/parsing/read_head.c						\
	font/parsing/read_hhea.c						\
	font/parsing/read_hmtx.c						\
	font/parsing/read_loca.c						\
	font/parsing/read_maxp.c						\
	font/parsing/ttf_get_table_offset.c				\
	font/parsing/ttf_parser.c						\
	\
	font/rendering/do_segments_intersect.c			\
	font/rendering/draw_glyph.c						\
	font/rendering/get_glyph_points.c				\
	font/rendering/get_quadratic_bezier_points.c	\
	font/rendering/is_point_inside_glyph.c			\
	font/rendering/write_centered_number_to_image.c	\
	font/rendering/write_centered_string_to_image.c	\
	\
	font/get_font.c	\
	\
	\
	gui/box/create_gui_box.c			\
	gui/box/default_gui_box_methods.c	\
	gui/box/destroy_t_gui_box.c			\
	gui/box/destroy_t_gui_boxes.c		\
	gui/box/get_box_offset.c			\
	gui/box/get_clicked_gui_box.c		\
	gui/box/mouse_utils.c				\
	\
	\
	gui/draw_icon/get_object/get_mesh_object.c	\
	gui/draw_icon/get_object/get_object.c		\
	\
	gui/draw_icon/draw_icon.c								\
	gui/draw_icon/draw_light_icon/draw_bottom_rectangles.c	\
	gui/draw_icon/draw_light_icon/draw_light_icon.c			\
	gui/draw_icon/draw_light_icon/draw_sides_rectangles.c	\
	gui/draw_icon/draw_light_icon/draw_top_rectangles.c		\
	\
	gui/float_input_box/create_float_input_box.c	\
	gui/float_input_box/draw_float_input_box.c		\
	gui/float_input_box/update_float_input_box.c	\
	\
	gui/main_box/menu_box/init_export_box.c		\
	gui/main_box/menu_box/init_menu_box.c		\
	gui/main_box/menu_box/init_settings_icon.c	\
	\
	gui/main_box/object_creation_box/init_object_creation_box.c		\
	gui/main_box/object_creation_box/light_create_on_click.c		\
	gui/main_box/object_creation_box/object_creation_on_clicks.c	\
	\
	gui/main_box/init_main_box.c		\
	\
	gui/object_list_box/create_light_gui_box.c			\
	gui/object_list_box/create_object_gui_box.c			\
	gui/object_list_box/get_selected_object_index.c		\
	gui/object_list_box/init_object_list_box.c			\
	gui/object_list_box/object_box_getters.c			\
	gui/object_list_box/object_list_gui_box_draw.c		\
	gui/object_list_box/object_list_gui_box_on_click.c	\
	gui/object_list_box/update_object_list_icons.c		\
	\
	gui/object_modification_box/init_color_picker/add_hover_color_circle.c	\
	gui/object_modification_box/init_color_picker/color_getter_functions.c	\
	gui/object_modification_box/init_color_picker/init_base_color_box.c		\
	gui/object_modification_box/init_color_picker/init_color_picker_box.c	\
	gui/object_modification_box/init_color_picker/init_rgb_picker.c			\
	gui/object_modification_box/init_color_picker/on_clicks.c				\
	\
	gui/object_modification_box/init_object_modification_box.c				\
	\
	gui/optional_boxes/add_mesh_object_box/click_mesh_box.c					\
	gui/optional_boxes/add_mesh_object_box/init_add_mesh_object_box.c		\
	gui/optional_boxes/add_mesh_object_box/load_mesh_objects.c				\
	gui/optional_boxes/add_mesh_object_box/mesh_object_selection_draw.c		\
	gui/optional_boxes/add_mesh_object_box/mesh_object_selection_on_click.c	\
	\
	gui/optional_boxes/settings_box/init_antialiasing_toggle_box.c	\
	gui/optional_boxes/settings_box/init_bounces_per_pixel_box.c	\
	gui/optional_boxes/settings_box/init_cam_fov_box.c				\
	gui/optional_boxes/settings_box/init_disable_shadows_box.c		\
	gui/optional_boxes/settings_box/init_max_resolution_reduction.c	\
	gui/optional_boxes/settings_box/init_min_resolution_reduction.c	\
	gui/optional_boxes/settings_box/init_reset_camera_peaking_box.c	\
	gui/optional_boxes/settings_box/init_settings_box.c				\
	\
	gui/optional_boxes/texture_box/outline_cap_picker/draw.c					\
	gui/optional_boxes/texture_box/outline_cap_picker/init_outline_cap_picker.c	\
	gui/optional_boxes/texture_box/outline_cap_picker/on_click.c				\
	\
	gui/optional_boxes/texture_box/selection_box/click_ppm_box.c						\
	gui/optional_boxes/texture_box/selection_box/init_selection_boxes.c					\
	gui/optional_boxes/texture_box/selection_box/load_textures_and_normal_maps.c		\
	gui/optional_boxes/texture_box/selection_box/textures_and_normal_maps_draw.c		\
	gui/optional_boxes/texture_box/selection_box/textures_and_normal_maps_on_click.c	\
	\
	gui/optional_boxes/texture_box/texture_normal_map_picker/draw.c								\
	gui/optional_boxes/texture_box/texture_normal_map_picker/init_texture_normal_map_picker.c	\
	gui/optional_boxes/texture_box/texture_normal_map_picker/on_click.c							\
	\
	gui/optional_boxes/texture_box/delete_box.c			\
	gui/optional_boxes/texture_box/init_texture_box.c	\
	\
	gui/optional_boxes/add_button_box.c			\
	gui/optional_boxes/add_plus_minus_box.c		\
	gui/optional_boxes/create_optional_box.c	\
	\
	gui/create_boxes_utils.c		\
	gui/create_horizontal_boxes.c	\
	gui/create_n_horizontal_boxes.c	\
	gui/create_vertical_boxes.c		\
	gui/get_boxes_decal.c			\
	gui/init_gui.c					\
	\
	\
	hooks/update_object_attributes_modification_box/add_boxes/cap_checkerboard_size_on_clicks/disable_cap_checkerboard.c	\
	hooks/update_object_attributes_modification_box/add_boxes/cap_checkerboard_size_on_clicks/x.c							\
	hooks/update_object_attributes_modification_box/add_boxes/cap_checkerboard_size_on_clicks/y.c							\
	\
	hooks/update_object_attributes_modification_box/add_boxes/normal_input_box_on_clicks/x.c	\
	hooks/update_object_attributes_modification_box/add_boxes/normal_input_box_on_clicks/y.c	\
	hooks/update_object_attributes_modification_box/add_boxes/normal_input_box_on_clicks/z.c	\
	\
	hooks/update_object_attributes_modification_box/add_boxes/outline_checkerboard_size_on_clicks/disable_outline_checkerboard.c	\
	hooks/update_object_attributes_modification_box/add_boxes/outline_checkerboard_size_on_clicks/x.c								\
	hooks/update_object_attributes_modification_box/add_boxes/outline_checkerboard_size_on_clicks/y.c								\
	\
	hooks/update_object_attributes_modification_box/add_boxes/position_input_box_on_clicks/x.c	\
	hooks/update_object_attributes_modification_box/add_boxes/position_input_box_on_clicks/y.c	\
	hooks/update_object_attributes_modification_box/add_boxes/position_input_box_on_clicks/z.c	\
	\
	hooks/update_object_attributes_modification_box/add_boxes/scale_input_box_on_clicks/x.c	\
	hooks/update_object_attributes_modification_box/add_boxes/scale_input_box_on_clicks/y.c	\
	hooks/update_object_attributes_modification_box/add_boxes/scale_input_box_on_clicks/z.c	\
	\
	hooks/update_object_attributes_modification_box/add_boxes/utils/add_toggle_box.c		\
	hooks/update_object_attributes_modification_box/add_boxes/utils/add_x_y_box.c			\
	hooks/update_object_attributes_modification_box/add_boxes/utils/add_x_y_z_box.c			\
	hooks/update_object_attributes_modification_box/add_boxes/utils/draw_toggle_box.c		\
	hooks/update_object_attributes_modification_box/add_boxes/utils/get_box_size.c			\
	hooks/update_object_attributes_modification_box/add_boxes/utils/get_x_y_input_box.c		\
	hooks/update_object_attributes_modification_box/add_boxes/utils/get_x_y_z_input_box.c	\
	hooks/update_object_attributes_modification_box/add_boxes/utils/init_description_box.c	\
	\
	hooks/update_object_attributes_modification_box/add_boxes/add_brightness_box.c								\
	hooks/update_object_attributes_modification_box/add_boxes/add_cap_checkerboard_size_box.c					\
	hooks/update_object_attributes_modification_box/add_boxes/add_cap_checkered_pattern_color_toggle_box.c		\
	hooks/update_object_attributes_modification_box/add_boxes/add_delete_box.c									\
	hooks/update_object_attributes_modification_box/add_boxes/add_height_box.c									\
	hooks/update_object_attributes_modification_box/add_boxes/add_normal_box.c									\
	hooks/update_object_attributes_modification_box/add_boxes/add_outline_checkerboard_size_box.c				\
	hooks/update_object_attributes_modification_box/add_boxes/add_outline_checkered_pattern_color_toggle_box.c	\
	hooks/update_object_attributes_modification_box/add_boxes/add_position_box.c								\
	hooks/update_object_attributes_modification_box/add_boxes/add_radius_box.c									\
	hooks/update_object_attributes_modification_box/add_boxes/add_reflection_box.c								\
	hooks/update_object_attributes_modification_box/add_boxes/add_scale_box.c									\
	hooks/update_object_attributes_modification_box/add_boxes/add_specular_reflection_box.c						\
	hooks/update_object_attributes_modification_box/add_boxes/add_texture_button.c								\
	\
	hooks/update_object_attributes_modification_box/get_box_category_index.c					\
	hooks/update_object_attributes_modification_box/init_cone_attributes_modification_box.c		\
	hooks/update_object_attributes_modification_box/init_cylinder_attributes_modification_box.c	\
	hooks/update_object_attributes_modification_box/init_light_attributes_modification_box.c	\
	hooks/update_object_attributes_modification_box/init_mesh_attributes_modification_box.c		\
	hooks/update_object_attributes_modification_box/init_plane_attributes_modification_box.c	\
	hooks/update_object_attributes_modification_box/init_sphere_attributes_modification_box.c	\
	hooks/update_object_attributes_modification_box/update_object_attributes_modification_box.c	\
	hooks/update_object_attributes_modification_box/update_float_input_boxes.c					\
	\
	hooks/button_press.c				\
	hooks/button_release.c				\
	hooks/deal_keys.c					\
	hooks/deal_mouse.c					\
	hooks/focus_handler.c				\
	hooks/key_press.c					\
	hooks/key_release.c					\
	hooks/motion_handler.c				\
	hooks/pressed_keys.c				\
	hooks/redraw_icons.c				\
	hooks/toggle_camera_lock.c			\
	hooks/toggle_gui.c					\
	hooks/update_color_picker_color.c	\
	\
	\
	image/change_image_color.c			\
	image/destroy_t_image.c				\
	image/draw_check_mark.c				\
	image/draw_circle.c					\
	image/draw_outline.c				\
	image/draw_plus_minus.c				\
	image/image.c						\
	image/mix_colors.c					\
	image/put_background.c				\
	image/put_image_to_image.c			\
	image/put_image_to_image_unsafe.c	\
	image/round_image_corners.c			\
	image/round_image_corners_utils.c	\
	\
	\
	init/init_engine_images.c								\
	init/init_engine.c										\
	init/init_mlx.c											\
	init/set_minirt_folder_as_current_working_directory.c	\
	\
	\
	interpolater/interpolate_main_lines.c	\
	interpolater/interpolate_ray_tracing.c	\
	interpolater/interpolate_sub_lines.c	\
	\
	\
	light/light.c	\
	light/lights.c	\
	\
	\
	material/checkerboard.c	\
	material/material.c		\
	material/normals_map.c	\
	material/texture.c		\
	\
	\
	math/matrix/matrix3.c			\
	math/matrix/matrix3_math.c		\
	math/matrix/matrix4.c			\
	math/matrix/matrix4_inverse.c	\
	math/matrix/matrix4_math.c		\
	math/matrix/rotation_matrix.c	\
	\
	math/quaternion/quaternion.c				\
	math/quaternion/quaternion_math.c			\
	math/quaternion/quaternion_operations.c		\
	math/quaternion/quaternion_rotation.c		\
	\
	math/vector/vector2.c				\
	math/vector/vector2_math.c			\
	math/vector/vector2_operations.c	\
	math/vector/vector3.c				\
	math/vector/vector3_limit.c			\
	math/vector/vector3_math.c			\
	math/vector/vector3_operations.c	\
	math/vector/vector3_rotation.c		\
	math/vector/vector4.c				\
	math/vector/vector4_math.c			\
	math/vector/vector4_operations.c	\
	\
	math/conversion.c	\
	math/equation.c		\
	math/modulo.c		\
	\
	\
	mlx_wrapper/get_screen_size.c		\
	mlx_wrapper/mouse_hide.c			\
	mlx_wrapper/mouse_move.c			\
	mlx_wrapper/mouse_show.c			\
	mlx_wrapper/put_image.c				\
	\
	\
	object/cone/create.c				\
	object/cone/transformations.c		\
	\
	object/cylinder/create.c			\
	object/cylinder/transformations.c	\
	\
	object/mesh/bounding_box.c			\
	object/mesh/cache.c					\
	object/mesh/create.c				\
	object/mesh/mesh_deep_copy.c		\
	object/mesh/transformations.c		\
	object/mesh/utils.c					\
	\
	object/plane/create.c				\
	object/plane/transformations.c		\
	\
	object/sphere/create.c				\
	object/sphere/transformations.c		\
	\
	object/bounding_box.c			\
	object/object_deep_copy.c		\
	object/clamp_rotation_degrees.c	\
	object/objects.c				\
	object/transformations.c		\
	object/calculate_cache.c		\
	\
	\
	parsing/line_parsing/utils/material/get_checkerboard_parsing_data.c	\
	parsing/line_parsing/utils/material/parse_cap_checkerboard.c		\
	parsing/line_parsing/utils/material/parse_cap_normal_map.c			\
	parsing/line_parsing/utils/material/parse_cap_texture.c				\
	parsing/line_parsing/utils/material/parse_outline_checkerboard.c	\
	parsing/line_parsing/utils/material/parse_outline_normal_map.c		\
	parsing/line_parsing/utils/material/parse_outline_texture.c			\
	parsing/line_parsing/utils/material/parse_reflection.c				\
	parsing/line_parsing/utils/material/parse_specular.c				\
	\
	parsing/line_parsing/utils/error.c						\
	parsing/line_parsing/utils/get_color.c					\
	parsing/line_parsing/utils/get_float.c					\
	parsing/line_parsing/utils/get_lighting_ratio.c			\
	parsing/line_parsing/utils/get_normalized_vector.c		\
	parsing/line_parsing/utils/get_position.c				\
	parsing/line_parsing/utils/get_rotation.c				\
	parsing/line_parsing/utils/get_vector3f.c				\
	\
	parsing/line_parsing/invalid_scene_content_line.c	\
	parsing/line_parsing/parse_ambient_light.c			\
	parsing/line_parsing/parse_camera.c					\
	parsing/line_parsing/parse_cone.c					\
	parsing/line_parsing/parse_cylinder.c				\
	parsing/line_parsing/parse_light.c					\
	parsing/line_parsing/parse_material.c				\
	parsing/line_parsing/parse_plane.c					\
	parsing/line_parsing/parse_mesh_object.c			\
	parsing/line_parsing/parse_sphere.c					\
	\
	parsing/obj_file/get_relevent_obj_lines.c	\
	parsing/obj_file/parse_obj_file.c			\
	parsing/obj_file/parse_line.c				\
	\
	parsing/free_scene_content.c	\
	parsing/get_scene_content.c		\
	parsing/parse_ppm_file.c		\
	parsing/parse_scene_content.c	\
	parsing/parsing.c				\
	\
	\
	ray_tracer/bvh/mesh/bounding_box.c		\
	ray_tracer/bvh/mesh/node.c				\
	ray_tracer/bvh/mesh/subdivide.c			\
	ray_tracer/bvh/mesh/tree.c				\
	\
	ray_tracer/bvh/objects/bounding_box.c	\
	ray_tracer/bvh/objects/node.c			\
	ray_tracer/bvh/objects/subdivide.c		\
	ray_tracer/bvh/objects/tree.c			\
	\
	ray_tracer/bvh/recalculate_bvh.c		\
	\
	\
	ray_tracer/camera/create.c		\
	ray_tracer/camera/movement.c	\
	ray_tracer/camera/projection.c	\
	ray_tracer/camera/ray.c			\
	ray_tracer/camera/rotation.c	\
	ray_tracer/camera/view.c		\
	\
	ray_tracer/rays/intersections/aabb.c				\
	ray_tracer/rays/intersections/cone.c				\
	ray_tracer/rays/intersections/cone_utils.c			\
	ray_tracer/rays/intersections/cylinder.c			\
	ray_tracer/rays/intersections/cylinder_caps.c		\
	ray_tracer/rays/intersections/cylinder_infinite.c	\
	ray_tracer/rays/intersections/intersection.c		\
	ray_tracer/rays/intersections/light.c				\
	ray_tracer/rays/intersections/mesh.c				\
	ray_tracer/rays/intersections/plane.c				\
	ray_tracer/rays/intersections/sphere.c				\
	ray_tracer/rays/intersections/objects_bvh.c			\
	ray_tracer/rays/intersections/mesh_bvh.c			\
	\
	ray_tracer/rays/context.c		\
	ray_tracer/rays/hit.c			\
	ray_tracer/rays/rays.c			\
	\
	ray_tracer/shade/light.c	\
	ray_tracer/shade/shade.c	\
	ray_tracer/shade/shadow.c	\
	\
	ray_tracer/texture/mapping.c		\
	ray_tracer/texture/normal.c			\
	ray_tracer/texture/texture.c		\
	\
	ray_tracer/post_processing.c			\
	ray_tracer/render.c						\
	ray_tracer/render_icon.c				\
	ray_tracer/render_ray.c					\
	ray_tracer/render_with_anti_aliasing.c	\
	\
	\
	ray_tracer_gui_api/add_and_remove_object_and_light.c	\
	ray_tracer_gui_api/get_clicked_object.c					\
	\
	\
	render_frame/print_fps_counter.c						\
	render_frame/put_raytraced_pixels_to_raytraced_image.c	\
	render_frame/render_frame.c								\
	render_frame/render_message.c							\
	render_frame/render_screen_shot_animation.c				\
	render_frame/render_user_interface.c					\
	render_frame/update_placed_object_position.c			\
	render_frame/update_scene.c								\
	\
	\
	threads/get_routine_data.c	\
	threads/mutex.c				\
	threads/threads.c			\
	\
	\
	vectors/mesh_faces.c		\
	vectors/vectors3f.c			\
	vectors/vectors3f_utils.c	\
	vectors/vectors3i.c			\
	vectors/vectors_int.c		\
	\
	close_engine.c		\
	color.c				\
	main.c				\
	scene.c
