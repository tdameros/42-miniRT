/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:29:29 by vfries            #+#    #+#             */
/*   Updated: 2023/01/09 01:03:57 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_split_size(char **strs)
{
	size_t	i;

	if (strs == NULL)
		return (0);
	i = 0;
	while (strs[i])
		i++;
	return (i);
}
