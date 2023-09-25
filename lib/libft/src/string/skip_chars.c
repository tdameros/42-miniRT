/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_chars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:56:53 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/23 22:56:53 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_skip_chars(const char *str, const char *chars_to_skip)
{
	if (chars_to_skip == NULL || ft_strlen(chars_to_skip) == 0)
		return ((char *)str);
	while (ft_strchr(chars_to_skip, *str) != NULL)
		str++;
	return ((char *)str);
}
