SRC				=\
	close_engine/close_engine.c		\
	close_engine/destroy_mlx.c		\
	\
	\
	hooks/key_press.c					\
	\
	\
	image/change_image_color.c			\
	image/destroy_t_image.c				\
	image/draw_outline.c				\
	image/image.c						\
	image/mix_colors.c					\
	image/put_background.c				\
	image/put_image_to_image.c			\
	image/put_image_to_image_unsafe.c	\
	\
	\
	init/init_engine_images.c								\
	init/init_engine.c										\
	init/init_mlx.c											\
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
	\
	\
	vectors/mesh_faces.c		\
	vectors/vectors3f.c			\
	vectors/vectors3f_utils.c	\
	vectors/vectors3i.c			\
	vectors/vectors_int.c		\
	\
	color.c				\
	main.c				\
	scene.c
