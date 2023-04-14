/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linked_list.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:01:01 by vfries            #+#    #+#             */
/*   Updated: 2023/03/03 17:54:55 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LINKED_LIST_H
# define FT_LINKED_LIST_H

# include <stddef.h>

// Doubly linked void *
typedef struct s_dlist
{
	struct s_dlist	*previous;
	void			*content;
	struct s_dlist	*next;
}	t_dlist;

t_dlist		*ft_dlst_get_next_free_current(t_dlist **lst, void (*del)(void *));
void		ft_dlst_of_dlst_clear(t_dlist **lst, void (*del)(void *));
void		ft_dlst_push(t_dlist **dst, t_dlist **src);
t_dlist		*ft_dlst_reverse(t_dlist **lst);
void		ft_dlstadd_back(t_dlist **lst, t_dlist *new);
void		ft_dlstadd_front(t_dlist **lst, t_dlist *new);
void		ft_dlstclear(t_dlist **lst, void (*del)(void *));
void		ft_dlstdelone(t_dlist *lst, void (*del)(void *));
void		ft_dlstiter(t_dlist *lst, void (*f)(void *));
t_dlist		*ft_dlstlast(t_dlist *lst);
t_dlist		*ft_dlstmap(t_dlist *lst, void *(*f)(void *), void (*del)(void *));
t_dlist		*ft_dlstnew(void *content);
size_t		ft_dlstsize(t_dlist *lst);

// void *
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list		*ft_lst_get_next_free_current(t_list **lst, void (*del)(void *));
char		*ft_lst_join_strs(t_list *str_list);
void		ft_lst_of_lst_clear(t_list **lst, void (*del)(void *));
void		ft_lst_push(t_list **dst, t_list **src);
t_list		*ft_lst_reverse(t_list **lst);
void		ft_lst_sort(t_list *lst, int (*f)(void *, void *));
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content);
size_t		ft_lstsize(t_list *lst);
void		ft_list_remove_if(t_list **begin_list, int (*cmp)(void *),
				void (*free_fct)(void *));

// int
typedef struct s_list_i
{
	int				content;
	struct s_list_i	*next;
}	t_list_i;

void		ft_lsti_add_back(t_list_i **lst, t_list_i *new);
void		ft_lsti_add_front(t_list_i **lst, t_list_i *new);
void		ft_lsti_clear(t_list_i **lst);
int			ft_lsti_cmp(t_list_i *lst_1, t_list_i *lst_2);
t_list_i	*ft_lsti_cpy(t_list_i *lst);
void		ft_lsti_delone(t_list_i *lst);
t_list_i	*ft_lsti_get_next_free_current(t_list_i **lst);
void		ft_lsti_iter(t_list_i *lst, void (*f)(int *));
t_list_i	*ft_lsti_last(t_list_i *lst);
t_list_i	*ft_lsti_map(t_list_i *lst, int (*f)(int));
t_list_i	*ft_lsti_new(int data);
void		ft_lsti_push(t_list_i **dst, t_list_i **src);
t_list_i	*ft_lsti_reverse(t_list_i **lst);
size_t		ft_lsti_size(t_list_i *lst);

#endif
