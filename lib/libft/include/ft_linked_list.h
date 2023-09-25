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

# include "ft_string.h"

// doubly_linked_void_ptr/

typedef struct s_dlist
{
	struct s_dlist	*previous;
	void			*content;
	struct s_dlist	*next;
}	t_dlist;

//	doubly_linked_void_ptr/dlst_get_next_free_current.c
t_dlist		*ft_dlst_get_next_free_current(t_dlist **lst, void (*del)(void *));

//	doubly_linked_void_ptr/dlst_of_dlst_clear.c
void		ft_dlst_of_dlst_clear(t_dlist **lst, void (*del)(void *));

//	doubly_linked_void_ptr/dlst_push.c
void		ft_dlst_push(t_dlist **dst, t_dlist **src);

//	doubly_linked_void_ptr/dlst_reverse.c
t_dlist		*ft_dlst_reverse(t_dlist **lst);

//	doubly_linked_void_ptr/dlstadd_back.c
void		ft_dlstadd_back(t_dlist **lst, t_dlist *new);

//	doubly_linked_void_ptr/dlstadd_front.c
void		ft_dlstadd_front(t_dlist **lst, t_dlist *new);

//	doubly_linked_void_ptr/dlstclear.c
void		ft_dlstclear(t_dlist **lst, void (*del)(void *));

//	doubly_linked_void_ptr/dlstdelone.c
void		ft_dlstdelone(t_dlist *lst, void (*del)(void *));

//	doubly_linked_void_ptr/dlstfirst.c
t_dlist		*ft_dlstfirst(const t_dlist *list);

//	doubly_linked_void_ptr/dlstiter.c
void		ft_dlstiter(t_dlist *lst, void (*f)(void *));

//	doubly_linked_void_ptr/dlstlast.c
t_dlist		*ft_dlstlast(t_dlist *lst);

//	doubly_linked_void_ptr/dlstmap.c
t_dlist		*ft_dlstmap(t_dlist *lst, void *(*f)(void *), void (*del)(void *));

//	doubly_linked_void_ptr/dlstnew.c
t_dlist		*ft_dlstnew(void *content);

//	doubly_linked_void_ptr/dlstsize.c
size_t		ft_dlstsize(t_dlist *lst);

//	int/

typedef struct s_list_i
{
	int				content;
	struct s_list_i	*next;
}	t_list_i;

//	int/lsti_add_back.c
void		ft_lsti_add_back(t_list_i **lst, t_list_i *new);

//	int/lsti_add_front.c
void		ft_lsti_add_front(t_list_i **lst, t_list_i *new);

//	int/lsti_clear.c
void		ft_lsti_clear(t_list_i **lst);

//	int/lsti_cmp.c
int			ft_lsti_cmp(t_list_i *lst_1, t_list_i *lst_2);

//	int/lsti_cpy.c
t_list_i	*ft_lsti_cpy(t_list_i *lst);

//	int/lsti_delone.c
void		ft_lsti_delone(t_list_i *lst);

//	int/lsti_get_next_free_current.c
t_list_i	*ft_lsti_get_next_free_current(t_list_i **lst);

//	int/lsti_iter.c
void		ft_lsti_iter(t_list_i *lst, void (*f)(int *));

//	int/lsti_last.c
t_list_i	*ft_lsti_last(t_list_i *lst);

//	int/lsti_map.c
t_list_i	*ft_lsti_map(t_list_i *lst, int (*f)(int));

//	int/lsti_new.c
t_list_i	*ft_lsti_new(int data);

//	int/lsti_push.c
void		ft_lsti_push(t_list_i **dst, t_list_i **src);

//	int/lsti_reverse.c
t_list_i	*ft_lsti_reverse(t_list_i **lst);

//	int/lsti_size.c
size_t		ft_lsti_size(t_list_i *lst);

//	void_ptr/

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

//	void_ptr/lst_get_next_free_current.c
t_list		*ft_lst_get_next_free_current(t_list **lst, void (*del)(void *));

//	void_ptr/lst_join_strs.c
char		*ft_lst_join_strs(t_list *str_list);

//	void_ptr/lst_join_t_strings.c
t_string	lst_join_t_strings(t_list *list, t_string separator);

//	void_ptr/lst_of_lst_clear.c
void		ft_lst_of_lst_clear(t_list **lst, void (*del)(void *));

//	void_ptr/lst_push.c
void		ft_lst_push(t_list **dst, t_list **src);

//	void_ptr/lst_remove_if.c
void		ft_list_remove_if(t_list **begin_list, int (*cmp)(void *),
				void (*free_fct)(void *));

//	void_ptr/lst_reverse.c
t_list		*ft_lst_reverse(t_list **lst);

//	void_ptr/lst_sort.c
void		ft_lst_sort(t_list *lst, int (*f)(void *, void *));

//	void_ptr/lstadd_back.c
void		ft_lstadd_back(t_list **lst, t_list *new);

//	void_ptr/lstadd_front.c
void		ft_lstadd_front(t_list **lst, t_list *new);

//	void_ptr/lstclear.c
void		ft_lstclear(t_list **lst, void (*del)(void *));

//	void_ptr/lstdelone.c
void		ft_lstdelone(t_list *lst, void (*del)(void *));

//	void_ptr/lstiter.c
void		ft_lstiter(t_list *lst, void (*f)(void *));

//	void_ptr/lstlast.c
t_list		*ft_lstlast(t_list *lst);

//	void_ptr/lstmap.c
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//	void_ptr/lstnew.c
t_list		*ft_lstnew(void *content);

//	void_ptr/lstsize.c
size_t		ft_lstsize(t_list *lst);

#endif
