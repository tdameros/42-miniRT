/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:18:57 by vfries            #+#    #+#             */
/*   Updated: 2023/04/21 03:18:58 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>

#include "libft.h"

#include "parsing.h"

static t_list	*get_all_lines(int fd);
static int		add_line(t_list **lines, char *line);
static char		***get_scene_content_from_lines(t_list *lines);

char	***get_scene_content(const int fd)
{
	char	***scene_content;
	t_list	*lines;

	lines = get_all_lines(fd);
	if (lines == NULL)
		return (NULL);
	scene_content = get_scene_content_from_lines(lines);
	ft_lstclear(&lines, &free);
	return (scene_content);
}

static t_list	*get_all_lines(int fd)
{
	t_list	*lines;
	char	*line;

	lines = NULL;
	errno = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (add_line(&lines, line) < 0)
		{
			ft_lstclear(&lines, &free);
			return (NULL);
		}
		line = get_next_line(fd);
	}
	if (errno != 0)
	{
		ft_lstclear(&lines, &free);
		return (NULL);
	}
	return (lines);
}

static int	add_line(t_list **lines, char *line)
{
	char	*trimmed_line;
	t_list	*lines_node;

	trimmed_line = ft_strtrim(line, " \n");
	free(line);
	if (trimmed_line == NULL)
		return (-1);
	if (ft_strlen(trimmed_line) == 0)
	{
		free(trimmed_line);
		return (0);
	}
	lines_node = ft_lstnew(trimmed_line);
	if (lines_node == NULL)
	{
		free(trimmed_line);
		return (-1);
	}
	ft_lstadd_front(lines, lines_node);
	return (0);
}

static char	***get_scene_content_from_lines(t_list *lines)
{
	char	***scene_content;
	size_t	lines_count;

	lines_count = ft_lstsize(lines);
	scene_content = malloc(sizeof(char **) * (lines_count + 1));
	if (scene_content == NULL)
		return (NULL);
	scene_content[lines_count] = NULL;
	while (lines_count--)
	{
		scene_content[lines_count] = ft_split_unless_in_quotes(lines->content,
				WHITE_SPACES);
//		scene_content[lines_count] = ft_split(lines->content, ' '); // TODO for mandatory part
		if (scene_content[lines_count] == NULL)
		{
			free_scene_content(scene_content);
			return (NULL);
		}
		lines = lines->next;
	}
	return (scene_content);
}
