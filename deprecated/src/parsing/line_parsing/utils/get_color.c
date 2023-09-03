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

static bool	is_not_valid_color(long long color);

int	get_color(char *color_string, t_color *color_destination)
{
	char		**color_split;
	long long	colors[3];

	color_split = ft_split(color_string, ',');
	if (color_split == NULL)
		return (-1);
	if (ft_split_len(color_split) != 3)
	{
		ft_free_split(color_split);
		return (-1);
	}
	colors[0] = ft_atoll(color_split[0]);
	colors[1] = ft_atoll(color_split[1]);
	colors[2] = ft_atoll(color_split[2]);
	ft_free_split(color_split);
	if (errno == ERANGE || errno == EINVAL || is_not_valid_color(colors[0])
		|| is_not_valid_color(colors[1]) || is_not_valid_color(colors[2]))
		return (-1);
	*color_destination = (t_color){
		.x = (int)colors[0],
		.y = (int)colors[1],
		.z = (int)colors[2],
	};
	return (0);
}

static bool	is_not_valid_color(long long color)
{
	return (color < 0 || color > 255);
}
