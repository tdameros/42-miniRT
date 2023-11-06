NAME				=	miniRT

include src.mk
SRC_PATH			=	src/
DIR_BUILD			=	.build/
OBJS				=	$(patsubst %.c, $(DIR_BUILD)%.o, $(SRC))
DEPS				=	$(patsubst %.c, $(DIR_BUILD)%.d, $(SRC))
DEPS_FLAGS			=	-MMD -MP
BASE_CFLAGS			=	-Wall -Wextra #-Werror
LOW_RESOLUTION_FLAGS = -D DEFAULT_MAX_RESOLUTION_REDUCTION=50 -D DEFAULT_MIN_RESOLUTION_REDUCTION=50 -D DEFAULT_ANTIALIASING_VALUE=0 #-D X_SCREEN_SIZE=500 -D Y_SCREEN_SIZE=500
BASE_DEBUG_CFLAGS	=	-g3 $(LOW_RESOLUTION_FLAGS)
DEBUG_CLFAGS		=	$(BASE_DEBUG_CFLAGS) -fsanitize=address
# DEBUG_CLFAGS		=	$(BASE_DEBUG_CFLAGS) -fsanitize=memory -fsanitize-memory-track-origins
#-ffast-math reduces calculation precision, need to check behaviour before using
OPTI_CFLAGS			=	-Ofast -march=native -flto -fno-signed-zeros -funroll-loops #-ffast-math
# CFLAGS				=	$(BASE_CFLAGS) -g3
# CFLAGS				=	$(BASE_CFLAGS) $(OPTI_CFLAGS) -g3
# CFLAGS				=	$(BASE_CFLAGS) $(BASE_DEBUG_CFLAGS)
CFLAGS				=	$(BASE_CFLAGS) $(OPTI_CFLAGS)
# CFLAGS			=	$(BASE_CFLAGS) $(DEBUG_CLFAGS)
# CFLAGS				=	$(BASE_CFLAGS) $(OPTI_CFLAGS) $(DEBUG_CLFAGS)
RM					=	rm -rf
AR					=	ar rcs

LIBFT_PATH		=	lib/libft/
LIBFT_INCLUDES	=	$(LIBFT_PATH)include/
LIBFT_L			=	-L $(LIBFT_PATH) -l ft
LIBFT_L_DEBUG	=	-L $(LIBFT_PATH) -l ft_debug
LIBFT_A			=	$(LIBFT_PATH)libft.a
LIBFT_A_DEBUG	=	$(LIBFT_PATH)libft_debug.a
MAKE_LIBFT		=	$(MAKE) -C $(LIBFT_PATH)


ASSETS_PATH			=	assets

OBJECTS_PATH		=	$(ASSETS_PATH)/objects
OBJECTS_ARCHIVE		=	$(OBJECTS_PATH)/objects.tar.gz
OBJECTS				=	$(OBJECTS_PATH)/*.obj
HIDE_OBJECTS		=	$(OBJECTS_PATH)/.*.obj

TEXTURES_PATH		=	$(ASSETS_PATH)/textures
TEXTURES_ARCHIVE	=	$(TEXTURES_PATH)/textures.tar.gz
TEXTURES			=	$(TEXTURES_PATH)/*.ppm
HIDE_TEXTURES		=	$(TEXTURES_PATH)/.*.ppm

NORMAL_MAPS_PATH	=	$(ASSETS_PATH)/normal_maps
NORMAL_MAPS_ARCHIVE	=	$(NORMAL_MAPS_PATH)/normal_maps.tar.gz
NORMAL_MAPS			=	$(NORMAL_MAPS_PATH)/*.ppm
HIDE_NORMAL_MAPS	=	$(NORMAL_MAPS_PATH)/.*.ppm


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
			./miniRT || true

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
	@if [ "$$(find $(OBJECTS_PATH) -maxdepth 1 -name '*.obj' -print)" ]; then \
		tar -czvf $(OBJECTS_ARCHIVE) $(OBJECTS); \
		rm -rf $(OBJECTS) $(HIDE_OBJECTS); \
    else \
      echo "No objects (*.obj) to compress found"; \
    fi
	@if [ "$$(find $(TEXTURES_PATH) -maxdepth 1 -name '*.ppm' -print)" ]; then \
		tar -czvf $(TEXTURES_ARCHIVE) $(TEXTURES); \
		rm -rf $(TEXTURES) $(HIDE_TEXTURES); \
    else \
      echo "No textures (*.ppm) to compress found"; \
    fi
	@if [ "$$(find $(NORMAL_MAPS_PATH) -maxdepth 1 -name '*.ppm' -print)" ]; then \
		tar -czvf $(NORMAL_MAPS_ARCHIVE) $(NORMAL_MAPS); \
		rm -rf $(NORMAL_MAPS) $(HIDE_NORMAL_MAPS); \
    else \
      echo "No normal maps (*.ppm) to compress found"; \
    fi

.PHONY: decompress
decompress:
	@if [ -e $(OBJECTS_ARCHIVE) ]; then\
        tar -xzvf $(OBJECTS_ARCHIVE); \
        rm -rf $(OBJECTS_ARCHIVE); \
    else \
      echo "No objects archive to decompress was found"; \
    fi
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


.PHONY: render
render: all
	find assets/scenes -name "*.rt" -not -path '*/.*' -exec ./miniRT {} \;