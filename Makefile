NAME			=	miniRT


SRC_PATH		=	src/

SRC				=\
	gui/box/create_gui_box.c			\
	gui/box/default_gui_box_methods.c	\
	gui/box/destroy_t_gui_box.c			\
	gui/box/get_clicked_gui_box.c		\
	gui/box/mouse_utils.c				\
	\
	gui/main_box/menu_box/init_menu_box.c		\
	gui/main_box/menu_box/init_settings_icon.c	\
	\
	gui/main_box/object_creation_box/init_object_creation_box.c		\
	gui/main_box/object_creation_box/object_creation_on_clicks.c	\
	\
	gui/main_box/icon_box_draw_method.c \
	gui/main_box/init_main_box.c		\
	\
	gui/object_modification_box/init_color_picker/add_hover_color_circle.c	\
	gui/object_modification_box/init_color_picker/color_getter_functions.c	\
	gui/object_modification_box/init_color_picker/init_base_color_box.c		\
	gui/object_modification_box/init_color_picker/init_color_picker_box.c	\
	gui/object_modification_box/init_color_picker/init_rgb_picker.c			\
	\
	gui/object_modification_box/init_object_attributes_modification_box.c	\
	gui/object_modification_box/init_object_modification_box.c				\
	\
	gui/create_boxes_utils.c		\
	gui/create_float_input_box.c	\
	gui/create_horizontal_boxes.c	\
	gui/create_n_horizontal_boxes.c	\
	gui/create_vertical_boxes.c		\
	gui/init_boxes.c				\
	\
	\
	hooks/update_object_attributes_modification_box/add_boxes/normal_input_box_on_clicks/x.c	\
	hooks/update_object_attributes_modification_box/add_boxes/normal_input_box_on_clicks/y.c	\
	hooks/update_object_attributes_modification_box/add_boxes/normal_input_box_on_clicks/z.c	\
	\
	hooks/update_object_attributes_modification_box/add_boxes/position_input_box_on_clicks/x.c	\
	hooks/update_object_attributes_modification_box/add_boxes/position_input_box_on_clicks/y.c	\
	hooks/update_object_attributes_modification_box/add_boxes/position_input_box_on_clicks/z.c	\
	\
	hooks/update_object_attributes_modification_box/add_boxes/add_height_box.c		\
	hooks/update_object_attributes_modification_box/add_boxes/add_normal_box.c		\
	hooks/update_object_attributes_modification_box/add_boxes/add_position_box.c	\
	hooks/update_object_attributes_modification_box/add_boxes/add_radius_box.c		\
	hooks/update_object_attributes_modification_box/add_boxes/add_x_y_z_box.c		\
	hooks/update_object_attributes_modification_box/add_boxes/get_x_y_z_input_box.c	\
	\
	hooks/update_object_attributes_modification_box/init_cylinder_attributes_modification_box.c	\
	hooks/update_object_attributes_modification_box/init_plane_attributes_modification_box.c	\
	hooks/update_object_attributes_modification_box/init_sphere_attributes_modification_box.c	\
	hooks/update_object_attributes_modification_box/update_object_attributes_modification_box.c	\
	\
	hooks/button_press.c	\
	hooks/button_release.c	\
	hooks/key_press.c		\
	\
	\
	image/destroy_t_image.c		\
	image/draw.c				\
	image/image.c				\
	image/put_image_to_image.c	\
	image/round_image_corners.c	\
	\
	\
	light/lights.c	\
	\
	\
	math/matrix/matrix3.c			\
	math/matrix/matrix3_math.c		\
	math/matrix/matrix3_rotation.c	\
	math/matrix/matrix4.c			\
	math/matrix/matrix4_inverse.c	\
	math/matrix/matrix4_math.c		\
	math/matrix/matrix4_round.c		\
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
	math/vector/vector3_angle.c			\
	math/vector/vector3_math.c			\
	math/vector/vector3_operations.c	\
	math/vector/vector3_random.c		\
	math/vector/vector3_rotation.c		\
	math/vector/vector4.c				\
	math/vector/vector4_math.c			\
	math/vector/vector4_operations.c	\
	\
	math/conversion.c	\
	math/equation.c		\
	\
	\
	object/cylinder.c			\
	object/cylinder_infinite.c	\
	object/material.c			\
	object/objects.c			\
	object/plane.c				\
	object/sphere.c				\
	\
	\
	parsing/line_parsing/utils/add_object_to_object_list.c	\
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
	parsing/line_parsing/parse_cylinder.c				\
	parsing/line_parsing/parse_light.c					\
	parsing/line_parsing/parse_plane.c					\
	parsing/line_parsing/parse_sphere.c					\
	\
	parsing/free_scene_content.c	\
	parsing/get_scene_content.c		\
	parsing/parse_scene_content.c	\
	parsing/parsing.c				\
	\
	\
	ray_tracer/camera/create.c		\
	ray_tracer/camera/movement.c	\
	ray_tracer/camera/projection.c	\
	ray_tracer/camera/ray.c			\
	ray_tracer/camera/view.c		\
	\
	ray_tracer/rays/intersections/cylinder.c			\
	ray_tracer/rays/intersections/cylinder_infinite.c	\
	ray_tracer/rays/intersections/plane.c				\
	ray_tracer/rays/intersections/sphere.c				\
	\
	ray_tracer/rays/rays.c			\
	ray_tracer/rays/collision.c		\
	\
	ray_tracer/shade/light.c	\
	ray_tracer/shade/shade.c	\
	ray_tracer/shade/shadow.c	\
	\
	ray_tracer/mapping.c	\
	ray_tracer/render.c		\
	\
	\
	ray_tracer_gui_api/get_clicked_object.c	\
	\
	\
	render_frame/print_fps_counter.c		\
	render_frame/render_frame.c				\
	render_frame/render_user_interface.c	\
	\
	\
	scene/create.c	\
	\
	\
	ttf_parser/parsing/get_glyph_offset.c				\
	ttf_parser/parsing/get_glyph_outlines.c				\
	ttf_parser/parsing/get_long_hor_metric.c			\
	ttf_parser/parsing/read_cmap.c						\
	ttf_parser/parsing/read_file.c						\
	ttf_parser/parsing/read_font_directory.c			\
	ttf_parser/parsing/read_format4.c					\
	ttf_parser/parsing/read_glyph_outline.c				\
	ttf_parser/parsing/read_glyph_outline_coordinates.c	\
	ttf_parser/parsing/read_head.c						\
	ttf_parser/parsing/read_hhea.c						\
	ttf_parser/parsing/read_hmtx.c						\
	ttf_parser/parsing/read_loca.c						\
	ttf_parser/parsing/read_maxp.c						\
	ttf_parser/parsing/ttf_get_table_offset.c			\
	ttf_parser/parsing/ttf_parser.c						\
	\
	ttf_parser/rendering/do_segments_intersect.c			\
	ttf_parser/rendering/draw_glyph.c						\
	ttf_parser/rendering/get_glyph_points.c					\
	ttf_parser/rendering/get_quadratic_bezier_points.c		\
	ttf_parser/rendering/write_centered_string_to_image.c	\
	\
	ttf_parser/get_font.c	\
	\
	\
	close_miniRT.c	\
	color.c			\
	init_minirt.c	\
	main.c

DIR_BUILD		=	.build/
OBJS			=	$(patsubst %.c, $(DIR_BUILD)%.o, $(SRC))
DEPS			=	$(patsubst %.c, $(DIR_BUILD)%.d, $(SRC))
DEPS_FLAGS		=	-MMD -MP
BASE_CFLAGS		=	-Wall -Wextra -Werror
DEBUG_CLFAGS	=	-g3 -fsanitize=address
#-ffast-math reduces calculation precision, need to check behaviour before using
OPTI_CFLAGS		=	-O3 -march=native #-ffast-math
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
    	$(MINILIBX_L)
    FRAMEWORKS =\
    	-framework OpenGL	\
    	-framework AppKit
endif

DEPENDENCIES =\
	$(LIBFT_A)	\
	$(MINILIBX_A)

.PHONY:		all
all:
			$(MAKE_LIBFT)
			$(MAKE_MINILIBX)
			$(MAKE) $(NAME)

.PHONY:		run
run:
			$(MAKE) -j
			./miniRT data/test.rt || true

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(FRAMEWORKS) $(LIBS) -o $(NAME)

.PHONY:	bonus
bonus:		all

.PHONY:	clean
clean:
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
