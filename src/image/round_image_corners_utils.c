/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_image_corners_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 01:47:39 by vfries            #+#    #+#             */
/*   Updated: 2023/09/24 03:40:47 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <math.h>

#include "image.h"

static bool	is_in_top_left_corner(float x, float y, float radius);
static bool	is_in_top_right_corner(float x, float y, float radius,
				t_image *image);
static bool	is_in_bottom_left_corner(float x, float y, float radius,
				t_image *image);
static bool	is_in_bottom_right_corner(float x, float y, float radius,
				t_image *image);

bool	is_point_in_corner(float x, float y, float radius, t_image *image)
{
	return (is_in_top_left_corner(x, y, radius)
		|| is_in_top_right_corner(x, y, radius, image)
		|| is_in_bottom_left_corner(x, y, radius, image)
		|| is_in_bottom_right_corner(x, y, radius, image));
}

static bool	is_in_top_left_corner(float x, float y, float radius)
{
	return (y < radius && x < radius
		&& powf(y - radius, 2) + powf(x - radius, 2) > powf(radius, 2));
}

static bool	is_in_top_right_corner(float x, float y, float radius,
				t_image *image)
{
	return (y < radius && x >= image->width - radius
		&& powf(y - radius, 2) + powf(x - image->width + radius, 2)
		> powf(radius, 2));
}

static bool	is_in_bottom_left_corner(float x, float y, float radius,
				t_image *image)
{
	return (y >= image->height - radius && x < radius
		&& powf(y - image->height + radius, 2)
		+ powf(x - radius, 2) > powf(radius, 2));
}

static bool	is_in_bottom_right_corner(float x, float y, float radius,
				t_image *image)
{
	return (y >= image->height - radius && x >= image->width - radius
		&& powf(y - image->height + radius, 2)
		+ powf(x - image->width + radius, 2) > powf(radius, 2));
}
