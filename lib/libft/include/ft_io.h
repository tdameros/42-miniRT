/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_io.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:00:10 by vfries            #+#    #+#             */
/*   Updated: 2023/04/09 00:21:04 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IO_H
# define FT_IO_H

# include <unistd.h>

# include "ft_string.h"

//	get_next_line/get_next_line.c
char		*get_next_line(int fd);

//	get_next_line/get_next_line_multi_fd.c
char		*get_next_line_multi_fd(int fd);

//	printf/printf.c
int			ft_printf(const char *format, ...);

//	get_files_in_directory.c
char		**ft_get_files_in_directory(const char *path, const char *extension,
				bool ignore_hidden_files);

//	print_error.c
ssize_t		ft_print_error(const char *str);

//	print_position_in_code.c
void		ft_print_position_in_code(const char *file, const char *function,
				const int line);

//	putchar_fd.c
ssize_t		ft_putchar_fd(const char c, int fd);

//	putendl_fd.c
ssize_t		ft_putendl_fd(const char *s, int fd);

//	putnbr_fd.c
ssize_t		ft_putnbr_fd(int n, int fd);

//	putstr.c
ssize_t		ft_putstr(const char *s);

//	putstr_fd.c
ssize_t		ft_putstr_fd(const char *s, int fd);

// readfile.c
t_string	ft_read_file(const char *file_name);

#endif
