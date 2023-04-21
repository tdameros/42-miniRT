/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:18:59 by vfries            #+#    #+#             */
/*   Updated: 2023/04/21 03:19:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

void	free_scene_content(char ***scene_content)
{
	size_t	i;

	i = 0;
	while (scene_content[i] != NULL)
	{
		ft_free_split(scene_content[i]);
		i++;
	}
	free(scene_content);
}
