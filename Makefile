NAME			=	miniRT


SRC_PATH		=	src/

SRC				=\
	export/scene/datetime.c	\
	export/scene/material.c	\
	export/scene/object.c	\
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
	\
	gui/object_modification_box/init_object_modification_box.c				\
	\
	gui/optional_boxes/settings_box/init_antialiasing_toggle_box.c	\
	gui/optional_boxes/settings_box/init_cam_fov_box.c				\
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
	hooks/update_object_attributes_modification_box/add_boxes/cap_checkerboard_size_on_clicks/x.c	\
	hooks/update_object_attributes_modification_box/add_boxes/cap_checkerboard_size_on_clicks/y.c	\
	\
	hooks/update_object_attributes_modification_box/add_boxes/normal_input_box_on_clicks/x.c	\
	hooks/update_object_attributes_modification_box/add_boxes/normal_input_box_on_clicks/y.c	\
	hooks/update_object_attributes_modification_box/add_boxes/normal_input_box_on_clicks/z.c	\
	\
	hooks/update_object_attributes_modification_box/add_boxes/outline_checkerboard_size_on_clicks/x.c	\
	hooks/update_object_attributes_modification_box/add_boxes/outline_checkerboard_size_on_clicks/y.c	\
	\
	hooks/update_object_attributes_modification_box/add_boxes/position_input_box_on_clicks/x.c	\
	hooks/update_object_attributes_modification_box/add_boxes/position_input_box_on_clicks/y.c	\
	hooks/update_object_attributes_modification_box/add_boxes/position_input_box_on_clicks/z.c	\
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
	hooks/update_object_attributes_modification_box/add_boxes/add_specular_reflection_box.c						\
	hooks/update_object_attributes_modification_box/add_boxes/add_texture_button.c								\
	\
	hooks/update_object_attributes_modification_box/get_box_category_index.c					\
	hooks/update_object_attributes_modification_box/init_cone_attributes_modification_box.c		\
	hooks/update_object_attributes_modification_box/init_cylinder_attributes_modification_box.c	\
	hooks/update_object_attributes_modification_box/init_light_attributes_modification_box.c	\
	hooks/update_object_attributes_modification_box/init_plane_attributes_modification_box.c	\
	hooks/update_object_attributes_modification_box/init_sphere_attributes_modification_box.c	\
	hooks/update_object_attributes_modification_box/update_object_attributes_modification_box.c	\
	hooks/update_object_attributes_modification_box/update_float_input_boxes.c					\
	\
	hooks/button_press.c				\
	hooks/button_release.c				\
	hooks/key_press.c					\
	hooks/key_release.c					\
	hooks/pressed_keys.c				\
	hooks/redraw_icons.c				\
	hooks/toggle_gui.c					\
	hooks/update_color_picker_color.c	\
	\
	\
	image/destroy_t_image.c		\
	image/draw.c				\
	image/draw_check_mark.c		\
	image/draw_outline.c		\
	image/image.c				\
	image/put_image_to_image.c	\
	image/round_image_corners.c	\
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
	object/cone/create.c				\
	object/cone/transformations.c		\
	\
	object/cylinder/create.c			\
	object/cylinder/transformations.c	\
	\
	object/mesh/create.c				\
	\
	object/plane/create.c				\
	object/plane/transformations.c		\
	\
	object/sphere/create.c				\
	object/sphere/transformations.c		\
	\
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
	\
	parsing/line_parsing/invalid_scene_content_line.c	\
	parsing/line_parsing/parse_ambient_light.c			\
	parsing/line_parsing/parse_camera.c					\
	parsing/line_parsing/parse_cone.c					\
	parsing/line_parsing/parse_cylinder.c				\
	parsing/line_parsing/parse_light.c					\
	parsing/line_parsing/parse_material.c				\
	parsing/line_parsing/parse_plane.c					\
	parsing/line_parsing/parse_sphere.c					\
	\
	parsing/obj_file/parse_obj_file.c	\
	parsing/obj_file/parse_line.c		\
	\
	parsing/free_scene_content.c	\
	parsing/get_scene_content.c		\
	parsing/parse_ppm_file.c		\
	parsing/parse_scene_content.c	\
	parsing/parsing.c				\
	\
	\
	ray_tracer/camera/create.c		\
	ray_tracer/camera/movement.c	\
	ray_tracer/camera/projection.c	\
	ray_tracer/camera/ray.c			\
	ray_tracer/camera/rotation.c	\
	ray_tracer/camera/view.c		\
	\
	ray_tracer/rays/intersections/cone.c				\
	ray_tracer/rays/intersections/cone_utils.c			\
	ray_tracer/rays/intersections/cylinder.c			\
	ray_tracer/rays/intersections/cylinder_caps.c		\
	ray_tracer/rays/intersections/cylinder_infinite.c	\
	ray_tracer/rays/intersections/intersection.c		\
	ray_tracer/rays/intersections/mesh.c				\
	ray_tracer/rays/intersections/plane.c				\
	ray_tracer/rays/intersections/sphere.c				\
	\
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
	ray_tracer/interpolate_ray_tracing.c	\
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
	render_frame/print_fps_counter.c		\
	render_frame/render_frame.c				\
	render_frame/render_user_interface.c	\
	\
	\
	vectors/mesh_faces.c	\
	vectors/vectors3f.c		\
	vectors/vectors3i.c		\
	\
	close_miniRT.c		\
	color.c				\
	init_minirt.c		\
	main.c

DIR_BUILD		=	.build/
OBJS			=	$(patsubst %.c, $(DIR_BUILD)%.o, $(SRC))
DEPS			=	$(patsubst %.c, $(DIR_BUILD)%.d, $(SRC))
DEPS_FLAGS		=	-MMD -MP
BASE_CFLAGS		=	-Wall -Wextra -Werror
DEBUG_CLFAGS	=	-g3 -fsanitize=address
#-ffast-math reduces calculation precision, need to check behaviour before using
OPTI_CFLAGS		=	-Ofast -march=native -flto -fno-signed-zeros -funroll-loops #-ffast-math
#CFLAGS			=	$(BASE_CFLAGS) -g3
CFLAGS			=	$(BASE_CFLAGS) $(OPTI_CFLAGS)
#CFLAGS			=	$(BASE_CFLAGS) $(DEBUG_CLFAGS)
#CFLAGS			=	$(BASE_CFLAGS) $(OPTI_CFLAGS) $(DEBUG_CLFAGS)
RM				=	rm -rf
AR				=	ar rcs

LIBFT_PATH		=	lib/libft/
LIBFT_INCLUDES	=	$(LIBFT_PATH)include/
LIBFT_L			=	-L $(LIBFT_PATH) -l ft
LIBFT_L_DEBUG	=	-L $(LIBFT_PATH) -l ft_debug
LIBFT_A			=	$(LIBFT_PATH)libft.a
LIBFT_A_DEBUG	=	$(LIBFT_PATH)libft_debug.a
MAKE_LIBFT		=	$(MAKE) -C $(LIBFT_PATH)


ASSETS_PATH			=	assets

TEXTURES_PATH		=	$(ASSETS_PATH)/textures
TEXTURES_ARCHIVE	=	$(TEXTURES_PATH)/textures.tar.gz
TEXTURES			=	$(TEXTURES_PATH)/*.ppm

NORMAL_MAPS_PATH	=	$(ASSETS_PATH)/normal_maps
NORMAL_MAPS_ARCHIVE	=	$(NORMAL_MAPS_PATH)/normal_maps.tar.gz
NORMAL_MAPS			=	$(NORMAL_MAPS_PATH)/*.ppm


OS	= $(shell uname -s)

ifeq ($(OS), Linux)
	MINILIBX_PATH		=	lib/minilibx-linux/
endif
ifeq ($(OS), Darwin)
	MINILIBX_PATH		=	lib/minilibx_opengl_20191021/
endif
MINILIBX_INCLUDES	=	$(MINILIBX_PATH)
MINILIBX_L			=	-L $(MINILIBX_PATH) -l mlx
MINILIBX_A			=	$(MINILIBX_PATH)libmlx.a
MAKE_MINILIBX		=	$(MAKE) -C $(MINILIBX_PATH)

DIR_INCS =\
	include/			\
	$(LIBFT_INCLUDES)	\
	$(MINILIBX_INCLUDES)
INCLUDES =\
	$(addprefix -I , $(DIR_INCS))

ifeq ($(OS), Linux)
	LIBS = \
    	-lm	\
    	$(LIBFT_L)	\
    	$(MINILIBX_L)	\
    	-lXext	\
    	-lX11
    FRAMEWORKS =
endif
ifeq ($(OS), Darwin)
	LIBS = \
    	-lm	\
    	$(LIBFT_L)	\
    	$(MINILIBX_L)	\
    	-L$(DIR_BUILD) -lget_window_size
    FRAMEWORKS =\
    	-framework OpenGL	\
    	-framework AppKit
endif

DEPENDENCIES =\
	$(LIBFT_A)	\
	$(MINILIBX_A)

.PHONY:		all
all:
			$(MAKE) decompress
			$(MAKE_LIBFT)
			$(MAKE_MINILIBX)
			$(MAKE) $(NAME)

.PHONY:		run
run:
			$(MAKE) -j
			./miniRT assets/scenes/test.rt || true

$(NAME):	$(OBJS) src/get_window_size.swift
	@if [ $(OS) = "Darwin" ]; then\
		swiftc -emit-library -module-name SwiftCode -o $(CURDIR)/$(DIR_BUILD)libget_window_size.a $(SRC_PATH)get_window_size.swift;\
	fi
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(FRAMEWORKS) $(LIBS) -o $(NAME)

.PHONY:	bonus
bonus:		all

.PHONY:	clean
clean:
			$(MAKE) compress
			$(MAKE_LIBFT) clean
			$(MAKE_MINILIBX) clean
			$(RM) $(DIR_BUILD)

.PHONY:	fclean
fclean:	clean
			$(MAKE_LIBFT) fclean
			$(MAKE_MINILIBX) clean # MINILIBX has no fclean
			$(RM) $(NAME)

.PHONY:	debug
debug: fclean
			$(MAKE) run -j CFLAGS="$(DEBUG_CLFAGS)"

.PHONY:	re
re:		fclean
			$(MAKE) all

-include $(DEPS)
$(DIR_BUILD)%.o : $(SRC_PATH)%.c $(LIBFT_A)
			@mkdir -p $(shell dirname $@)
			$(CC) $(CFLAGS) $(DEPS_FLAGS) $(INCLUDES) -c $< -o $@


.PHONY: compress
compress:
	@if [ "$$(find $(TEXTURES_PATH) -maxdepth 1 -name '*.ppm' -print)" ]; then \
		tar -czvf $(TEXTURES_ARCHIVE) $(TEXTURES); \
		rm -rf $(TEXTURES); \
    else \
      echo "No textures (*.ppm) to compress found"; \
    fi
	@if [ "$$(find $(NORMAL_MAPS_PATH) -maxdepth 1 -name '*.ppm' -print)" ]; then \
		tar -czvf $(NORMAL_MAPS_ARCHIVE) $(NORMAL_MAPS); \
		rm -rf $(NORMAL_MAPS); \
    else \
      echo "No normal maps (*.ppm) to compress found"; \
    fi

.PHONY: decompress
decompress:
	@if [ -e $(TEXTURES_ARCHIVE) ]; then\
        tar -xzvf $(TEXTURES_ARCHIVE); \
        rm -rf $(TEXTURES_ARCHIVE); \
    else \
      echo "No textures archive to decompress was found"; \
    fi
	@if [ -e $(NORMAL_MAPS_ARCHIVE) ]; then\
        tar -xzvf $(NORMAL_MAPS_ARCHIVE); \
        rm -rf $(NORMAL_MAPS_ARCHIVE); \
    else \
      echo "No normal maps archive to decompress was found"; \
    fi
