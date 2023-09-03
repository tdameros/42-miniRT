/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:19:16 by vfries            #+#    #+#             */
/*   Updated: 2023/04/21 03:30:57 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "libft.h"

#include "engine.h"

static bool	is_not_valid_color(float color);

int	get_color(char *color_string, t_color *color_destination)
{
	char		**color_split;

	color_split = ft_split(color_string, ',');
	if (color_split == NULL)
		return (-1);
	if (ft_split_len(color_split) != 3)
	{
		ft_free_split(color_split);
		return (-1);
	}
	color_destination->x = ft_atof(color_split[0]);
	color_destination->y = ft_atof(color_split[1]);
	color_destination->z = ft_atof(color_split[2]);
	ft_free_split(color_split);
	if (errno == ERANGE || errno == EINVAL
		|| is_not_valid_color(color_destination->x)
		|| is_not_valid_color(color_destination->y)
		|| is_not_valid_color(color_destination->z))
		return (-1);
	return (0);
}

static bool	is_not_valid_color(float color)
{
	return (color < 0.f || color > 255.f);
}
