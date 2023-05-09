NAME			=	miniRT


SRC_PATH		=	src/

SRC				=\
	hooks/button_press.c	\
	hooks/key_press.c		\
	\
	\
	init/init_gui/object_modification_gui_box/init_color_picker/add_hover_color_circle.c	\
	init/init_gui/object_modification_gui_box/init_color_picker/color_getter_functions.c	\
	init/init_gui/object_modification_gui_box/init_color_picker/init_base_color_box.c		\
	init/init_gui/object_modification_gui_box/init_color_picker/init_color_picker_box.c		\
	init/init_gui/object_modification_gui_box/init_color_picker/init_rgb_picker.c			\
											 \
	init/init_gui/object_modification_gui_box/init_object_modification_gui_box.c			\
				 \
	init/init_gui/main_gui_box/menu_box/init_menu_gui_box.c		\
	init/init_gui/main_gui_box/menu_box/init_settings_icon.c	\
							  \
	init/init_gui/main_gui_box/object_creation_box/init_object_creation_gui_box.c	\
							  \
	init/init_gui/main_gui_box/icon_box_draw_method.c	\
	init/init_gui/main_gui_box/init_main_gui_box.c		\
				 \
	init/init_gui/init_gui_boxes.c	\
	init/init_gui/mouse_in_box.c	\
		\
		\
	init/parsing/line_parsing/utils/add_object_to_object_list.c	\
	init/parsing/line_parsing/utils/error.c						\
	init/parsing/line_parsing/utils/get_color.c					\
	init/parsing/line_parsing/utils/get_double.c				\
	init/parsing/line_parsing/utils/get_lighting_ratio.c		\
	init/parsing/line_parsing/utils/get_normalized_vector.c		\
	init/parsing/line_parsing/utils/get_position.c				\
							 \
	init/parsing/line_parsing/invalid_scene_content_line.c	\
	init/parsing/line_parsing/parse_ambient_light.c			\
	init/parsing/line_parsing/parse_camera.c				\
	init/parsing/line_parsing/parse_cylinder.c				\
	init/parsing/line_parsing/parse_light.c					\
	init/parsing/line_parsing/parse_plane.c					\
	init/parsing/line_parsing/parse_sphere.c				\
				\
	init/parsing/free_scene_content.c	\
	init/parsing/get_scene_content.c	\
	init/parsing/parse_scene_content.c	\
	init/parsing/parsing.c				\
		\
	init/init_minirt.c		\
	\
	\
	ray_tracer/camera/create.c		\
	ray_tracer/camera/movement.c	\
	ray_tracer/camera/projection.c	\
	ray_tracer/camera/ray.c			\
	ray_tracer/camera/view.c		\
			  \
	ray_tracer/math/matrix/matrix3.c			\
	ray_tracer/math/matrix/matrix3_math.c		\
	ray_tracer/math/matrix/matrix3_rotation.c	\
	ray_tracer/math/matrix/matrix4.c			\
	ray_tracer/math/matrix/matrix4_inverse.c	\
	ray_tracer/math/matrix/matrix4_math.c		\
				   \
	ray_tracer/math/vector/vector2.c			\
	ray_tracer/math/vector/vector2_math.c		\
	ray_tracer/math/vector/vector2_operations.c	\
	ray_tracer/math/vector/vector3.c			\
	ray_tracer/math/vector/vector3_math.c		\
	ray_tracer/math/vector/vector3_operations.c	\
	ray_tracer/math/vector/vector3_rotation.c	\
	ray_tracer/math/vector/vector4.c			\
	ray_tracer/math/vector/vector4_math.c		\
	ray_tracer/math/vector/vector4_operations.c	\
				   \
	ray_tracer/math/conversion.c	\
			  \
	ray_tracer/object/sphere.c	\
			  \
	ray_tracer/scene/create.c	\
			  \
	ray_tracer/ray.c	\
	ray_tracer/render.c	\
	\
	\
	render_frame/print_fps_counter.c		\
	render_frame/render_frame.c				\
	render_frame/render_user_interface.c	\
	\
	\
	structs/gui_box/create_gui_box.c			\
	structs/gui_box/default_gui_box_methods.c	\
	structs/gui_box/destroy_t_gui_box.c			\
	structs/gui_box/get_clicked_gui_box.c		\
		   \
	structs/image/destroy_t_image.c		\
	structs/image/image.c				\
	structs/image/put_image_to_image.c	\
	structs/image/round_image_corners.c	\
	\
	\
	close_miniRT.c	\
	main.c			\
	color.c

DIR_BUILD		=	.build/
OBJS			=	$(patsubst %.c, $(DIR_BUILD)%.o, $(SRC))
DEPS			=	$(patsubst %.c, $(DIR_BUILD)%.d, $(SRC))
DEPS_FLAGS		=	-MMD -MP
BASE_CFLAGS		=	-Wall -Wextra -Werror
DEBUG_CLFAGS	=	-g3 -fsanitize=address
#-ffast-math reduces calculation precision, need to check behaviour before using
OPTI_CFLAGS		=	-O3 -march=native #-ffast-math
#CFLAGS			=	$(BASE_CFLAGS) $(OPTI_CFLAGS)
#CFLAGS			=	$(BASE_CFLAGS) $(DEBUG_CLFAGS)
CFLAGS			=	$(BASE_CFLAGS) $(OPTI_CFLAGS)
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

.PHONY:	re
re:		fclean
			$(MAKE) all

-include $(DEPS)
$(DIR_BUILD)%.o : $(SRC_PATH)%.c $(LIBFT_A)
			@mkdir -p $(shell dirname $@)
			$(CC) $(CFLAGS) $(DEPS_FLAGS) $(INCLUDES) -c $< -o $@
