/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:45:16 by vfries            #+#    #+#             */
/*   Updated: 2023/01/09 01:04:15 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"
#include "ft_string.h"
#include <stddef.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*start_s1;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	if (*s1 == '\0')
		return (ft_calloc(1, sizeof(char)));
	start_s1 = s1;
	while (*s1)
		s1++;
	s1--;
	while (ft_strchr(set, *s1))
		s1--;
	return (ft_substr(start_s1, 0, s1 - start_s1 + 1));
}
