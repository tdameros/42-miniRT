/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 02:37:37 by vfries            #+#    #+#             */
/*   Updated: 2022/11/13 18:06:58 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef enum e_bool
{
	FALSE,
	TRUE
}					t_bool;

typedef struct s_lst
{
	char			*data;
	struct s_lst	*next;
}					t_lst;

void				ft_bzero_stop_at_zero(void *s, size_t n);
void				lst_add_front(t_lst **head, char *data);
void				*lst_free(t_lst *lst);
void				lst_reverse(t_lst **lst);
char				*get_next_line(int fd);

#endif
