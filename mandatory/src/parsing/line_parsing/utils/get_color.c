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

#include "libft.h"

#include "engine.h"
#include "parsing.h"

static bool	is_not_valid_color(float color);

int	get_color(const char *color_string, t_color *color_destination)
{
	if (get_vector3f(color_string, color_destination) < 0)
		return (-1);
	if (is_not_valid_color(color_destination->x)
		|| is_not_valid_color(color_destination->y)
		|| is_not_valid_color(color_destination->z))
		return (-1);
	return (0);
}

static bool	is_not_valid_color(float color)
{
	return (color < 0.f || color > 255.f);
}
