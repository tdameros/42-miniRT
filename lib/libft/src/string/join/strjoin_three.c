/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:55:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/06 22:55:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3)
{
	char	*result;
	size_t	result_size;

	if (s1 == NULL || s2 == NULL || s3 == NULL)
		return (NULL);
	result_size = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	result = ft_calloc(result_size, sizeof(*result));
	if (result == NULL)
		return (NULL);
	ft_strlcat(result, s1, result_size);
	ft_strlcat(result, s2, result_size);
	ft_strlcat(result, s3, result_size);
	return (result);
}
