/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 02:08:39 by vfries            #+#    #+#             */
/*   Updated: 2023/03/09 17:18:33 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_skip_set(const char *str, const char *set)
{
	if (*set == '\0')
		return ((char *) str);
	while (*str != '\0' && ft_strchr(set, *str) != NULL)
		str++;
	return ((char *) str);
}
