/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_getter_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 01:50:29 by vfries            #+#    #+#             */
/*   Updated: 2023/04/28 01:50:29 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

int	get_increasing_color(float color, float x, float decal,
				float ratio)
{
	return (roundf(color * ((x - decal) / ratio)));
}

int	get_decreasing_color(float color, float x, float decal,
				float ratio)
{
	return (roundf(color * (1.0 - ((x - decal) / ratio))));
}

int	get_base_color(float color, float x, float decal, float ratio)
{
	(void)x;
	(void)decal;
	(void)ratio;
	return (color);
}
