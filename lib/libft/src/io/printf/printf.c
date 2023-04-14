/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:32:51 by vfries            #+#    #+#             */
/*   Updated: 2023/03/01 12:35:15 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linked_list.h"
#include "ft_string.h"
#include "ft_io.h"
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

void	free_content(void *content);
char	*get_final_str(t_list *line_lst, int *char_written);
char	*format(const char **str_format, va_list *args);

char	*strdup_till_format(const char **str_format)
{
	const char	*result_start;

	result_start = *str_format;
	while (**str_format && **str_format != '%')
		(*str_format)++;
	return (ft_substr(result_start, 0, *str_format - result_start));
}

void	*clear_str_list_and_return_null(t_list **str_list)
{
	ft_lstclear(str_list, &free_content);
	return (NULL);
}

int	add_str_to_str_list(t_list **str_list, t_list *new)
{
	static t_list	*last_elem = NULL;

	if (new == NULL)
		return (-1);
	if (*str_list == NULL)
	{
		*str_list = new;
		last_elem = new;
		return (0);
	}
	last_elem->next = new;
	last_elem = new;
	return (0);
}

t_list	*get_str_list(const char *str_format, va_list *args)
{
	char	*str;
	t_list	*str_list;

	if (*str_format == '\0')
		return ((void *)-1);
	str_list = NULL;
	while (*str_format)
	{
		if (*str_format == '%')
		{
			str_format++;
			str = format(&str_format, args);
			str_format++;
		}
		else
			str = strdup_till_format(&str_format);
		if (str == NULL)
			clear_str_list_and_return_null(&str_list);
		if (str != (void *)-2)
			if (add_str_to_str_list(&str_list, ft_lstnew(str)) == -1)
				return (clear_str_list_and_return_null(&str_list));
	}
	return (str_list);
}

int	ft_printf(const char *str_format, ...)
{
	int		char_written;
	t_list	*str_list;
	va_list	args;
	char	*final_str;

	va_start(args, str_format);
	str_list = get_str_list(str_format, &args);
	va_end(args);
	if (str_list == NULL)
		return (-1);
	if (str_list == (void *)-1)
		return (0);
	final_str = get_final_str(str_list, &char_written);
	if (final_str == NULL)
	{
		ft_lstclear(&str_list, &free_content);
		return (-1);
	}
	if (write(STDOUT_FILENO, final_str, char_written) == -1)
		char_written = -1;
	free(final_str);
	ft_lstclear(&str_list, &free_content);
	return (char_written);
}
