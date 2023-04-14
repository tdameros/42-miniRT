/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:06:05 by vfries            #+#    #+#             */
/*   Updated: 2023/01/09 01:03:55 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_split(void *strs)
{
	size_t	i;

	if (strs == NULL)
		return ;
	i = -1;
	while (((char **)strs)[++i])
		free(((char **)strs)[i]);
	free(strs);
}
