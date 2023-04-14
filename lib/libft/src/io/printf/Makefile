# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/07 19:13:43 by vfries            #+#    #+#              #
#    Updated: 2022/11/20 04:04:47 by vfries           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME		=	libftprintf.a

SRCS		=

DIR_OBJS	=	.objs/

OBJS		=	${addprefix ${DIR_OBJS},${SRCS:.c=.o}}

FLAG		=	-Wall -Wextra -Werror

HEADERS		=	ft_printf.h

INCLUDES	=	${LIBFT_PATH}

LIBFT_PATH	=	libft

LIBFT_A		=	${LIBFT_PATH}/libft.a

CC			=	cc

RMF			=	rm -f

MAKE_LIBFT	=	cd ${LIBFT_PATH} && ${MAKE}

MKDIR		=	mkdir -p

all:			${DIR_OBJS}
			@${MAKE_LIBFT}
			@${MAKE} -j ${NAME}

${DIR_OBJS}:
			echo ${OBJS} | tr ' ' '\n'\
				| sed 's|\(.*\)/.*|\1|'\
				| sed 's/^/${MKDIR} /'\
				| sh -s
			# Prints all OBJS. 1 per line
				# Removes the .o file names
				# Adds mkdir -p at start of the line
				# Executes the script (Creates all folders)

get_libft_objs_path:
			@${MAKE_LIBFT} echo_objs\
				| sed 's/^/ /'\
				| sed -e 's/ ./ ${LIBFT_PATH}/g'

$(NAME):		${OBJS}
			ar rcs ${NAME} ${OBJS} ${shell ${MAKE} get_libft_objs_path}

${DIR_OBJS}%.o:	%.c ${HEADERS} Makefile ${LIBFT_A}
			${CC} ${FLAG} -I ${INCLUDES} -c $< -o $@

clean:
			${MAKE_LIBFT} clean
			${RMF} ${OBJS} ${OBJS_BONUS}

fclean:			clean
			${RMF} ${LIBFT_A}
			${RMF} ${NAME}

re:				fclean
			${MAKE} all

.PHONY:			all get_libft_objs_path clean fclean re
