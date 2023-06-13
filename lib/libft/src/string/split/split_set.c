/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 20:35:08 by vfries            #+#    #+#             */
/*   Updated: 2023/01/09 01:03:56 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>

static size_t	ft_get_word_count(const char *s, char *set)
{
	size_t	word_count;

	word_count = 0;
	while (*s)
	{
		if (ft_strchr(set, *s) == NULL)
			word_count++;
		while (*s && ft_strchr(set, *s) == NULL)
			s++;
		if (*s)
			s++;
	}
	return (word_count);
}

static char	**ft_free_result(char **result, size_t i)
{
	while (i--)
		free(result[i]);
	free(result);
	return (NULL);
}

static char const	*skip_set(char const *s, char *set)
{
	while (*s && ft_strchr(set, *s))
		s++;
	return (s);
}

static size_t	get_end(char const *s, char *set)
{
	size_t	end;

	end = 0;
	while (s[end] && ft_strchr(set, s[end]) == NULL)
		end++;
	return (end);
}

char	**ft_split_set(char const *s, char *set)
{
	size_t	word_count;
	char	**result;
	size_t	i;
	size_t	end;

	if (s == NULL)
		return (NULL);
	word_count = ft_get_word_count(s, set);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		s = skip_set(s, set);
		end = get_end(s, set);
		result[i] = ft_substr(s, 0, end);
		if (result[i] == NULL)
			return (ft_free_result(result, i));
		s += end;
		i++;
	}
	result[i] = NULL;
	return (result);
}
