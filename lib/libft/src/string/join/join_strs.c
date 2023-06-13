/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_strs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:08:30 by vfries            #+#    #+#             */
/*   Updated: 2023/01/09 01:03:34 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>

static size_t	get_total_len(char **strs, size_t sep_len)
{
	size_t	ret;
	size_t	i;

	ret = 0;
	i = -1;
	while (strs[++i] != NULL)
		ret += ft_strlen(strs[i]) + sep_len;
	if (ret != 0)
		ret -= sep_len;
	return (ret);
}

static size_t	add_str(char *cursor, char const *str)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		*cursor++ = *str++;
		i++;
	}
	return (i);
}

char	*ft_join_strs(char **strs, char const *sep)
{
	char	*ret;
	char	*cursor;
	size_t	i;

	ret = malloc(sizeof(char) * (get_total_len(strs, ft_strlen(sep)) + 1));
	if (ret == NULL)
		return (NULL);
	cursor = ret;
	i = 0;
	while (strs[i] != NULL)
	{
		cursor += add_str(cursor, strs[i++]);
		if (strs[i] != NULL)
			cursor += add_str(cursor, sep);
	}
	*cursor = '\0';
	return (ret);
}
