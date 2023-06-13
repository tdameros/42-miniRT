/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:21:43 by vfries            #+#    #+#             */
/*   Updated: 2023/01/09 01:03:38 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	result_size;
	size_t	len_s1;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	len_s1 = ft_strlen(s1);
	result_size = len_s1 + ft_strlen(s2) + 1;
	result = malloc(result_size);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, result_size);
	ft_strlcpy(result + len_s1, s2, result_size - len_s1);
	return (result);
}
