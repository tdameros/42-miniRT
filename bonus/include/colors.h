/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:35:25 by vfries            #+#    #+#             */
/*   Updated: 2022/12/09 19:42:02 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include <stdint.h>

# include "math/vector.h"

enum
{
	COLOR_TRANSPARENT = 0xFF000000,
	COLOR_BLACK = 0x00000000,
	COLOR_WHITE = 0x00FFFFFF,
	COLOR_LIGHT_GREY = 0x007f7f7f,
	COLOR_BLUE = 0x000000FF,
	COLOR_SEA_BLUE = 0x00003D60,
	COLOR_SAND = 0x00C2B280,
	COLOR_LIGHT_GRASS = 0x00326500,
	COLOR_MID_GRASS = 0x00254C00,
	COLOR_DARK_GRASS = 0x00193200,
	COLOR_ROCK = 0x005A4D41,
	COLOR_SNOW_WHITE = 0x00FFFAFA,
	COLOR_RED = 0x00FF0000,
};

typedef t_vector3f	t_color;

//	color.c
unsigned int	rgb_to_uint(t_color color);
unsigned int	vec_rgb_to_uint(t_color color);
uint8_t			get_transparency(unsigned int color);
float			get_transparency_ratio(unsigned int color);
t_color			get_t_color_from_uint(unsigned int color);

#endif
