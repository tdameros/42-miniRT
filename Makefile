NAME			=	miniRT


SRC_PATH		=	src/

SRC				=\
	gui_box/create_gui_box.c			\
	gui_box/default_gui_box_methods.c	\
\
\
	hooks/button_press.c	\
	hooks/key_press.c		\
\
\
	image/image.c				\
	image/round_image_corners.c	\
\
\
	init/init_gui/init_gui_boxes.c						\
	init/init_gui/init_object_creation_gui_box.c		\
	init/init_gui/init_object_modification_gui_box.c	\
	\
	init/init_minirt.c		\
\
\
	close_miniRT.c	\
	main.c			\
	render_frame.c

DIR_BUILD		=	.build/
OBJS			=	$(patsubst %.c, $(DIR_BUILD)%.o, $(SRC))
DEPS			=	$(patsubst %.c, $(DIR_BUILD)%.d, $(SRC))
DEPS_FLAGS		=	-MMD -MP
CFLAGS			=	-Wall -Wextra -Werror -g3 -fsanitize=address
RM				=	rm -rf
AR				=	ar rcs

LIBFT_PATH		=	lib/libft/
LIBFT_INCLUDES	=	$(LIBFT_PATH)include/
LIBFT_L			=	-L $(LIBFT_PATH) -l ft
LIBFT_L_DEBUG	=	-L $(LIBFT_PATH) -l ft_debug
LIBFT_A			=	$(LIBFT_PATH)libft.a
LIBFT_A_DEBUG	=	$(LIBFT_PATH)libft_debug.a
MAKE_LIBFT		=	$(MAKE) -C $(LIBFT_PATH)

MINILIBX_PATH		=	lib/minilibx_opengl_20191021/
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

LIBS = \
	-lm	\
	$(LIBFT_L)	\
	$(MINILIBX_L)
FRAMEWORKS =\
	-framework OpenGL	\
	-framework AppKit

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
