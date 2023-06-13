/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:32:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/07 16:32:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrstr(const char *haystack, const char *needle)
{
	char	*result;
	size_t	needle_len;

	if (*needle == '\0')
		return ((char *)haystack);
	result = NULL;
	needle_len = ft_strlen(needle);
	while (*haystack != '\0')
	{
		if (ft_strncmp(haystack, needle, needle_len) == 0)
			result = (char *) haystack;
		haystack++;
	}
	return (result);
}
