/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_glyph_points.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:59:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/14 17:59:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "font/ttf_parser.h"
#include "font/render.h"
#include "math/vector.h"

#define NB_OF_POINT_ON_CURVE_TO_GENERATE 4

static int	get_contour_points(int16_t contour_index,
				const t_glyph_outline *glyph, t_vector *current_points,
				t_vector *dest);
static int	get_points(uint32_t *i, const t_glyph_outline *glyph,
				t_contour_info contour_info, t_vector *current_points);
static int	handle_on_curve(t_vector *current_points,
				const t_glyph_outline *glyph, uint32_t *i);
static int	handle_off_curve(t_vector *current_points,
				const t_glyph_outline *glyph, uint32_t *i,
				t_contour_info contour_info);

int	get_glyph_points(t_vector *dest, const t_glyph_outline *glyph,
		size_t **end_of_generated_contours)
{
	int16_t			contour_index;
	t_vector		current_points;

	*end_of_generated_contours = malloc(sizeof(**end_of_generated_contours)
			* glyph->number_of_contours);
	if (*end_of_generated_contours == NULL)
		return (-1);
	ft_vector_create(dest, sizeof(t_vector2f), 0);
	ft_vector_create(&current_points, sizeof(t_vector2f), 0);
	contour_index = -1;
	while (++contour_index < glyph->number_of_contours)
	{
		if (get_contour_points(contour_index, glyph, &current_points, dest) < 0)
		{
			ft_vector_destroy(&current_points);
			ft_vector_destroy(dest);
			return (-1);
		}
		(*end_of_generated_contours)[contour_index] = dest->length;
	}
	ft_vector_destroy(&current_points);
	ft_vector_minimize_size(dest);
	return (0);
}

static int	get_contour_points(const int16_t contour_index,
				const t_glyph_outline *glyph, t_vector *current_points,
				t_vector *dest)
{
	uint32_t		i;
	t_contour_info	contour_info;

	if (contour_index == 0)
		contour_info.contour_start_index = 0;
	else
		contour_info.contour_start_index
			= glyph->end_pts_of_contours[contour_index - 1] + 1;
	if (contour_index == 0)
		contour_info.contour_len = \
		glyph->end_pts_of_contours[contour_index] + 1;
	else
		contour_info.contour_len = glyph->end_pts_of_contours[contour_index]
			- glyph->end_pts_of_contours[contour_index - 1];
	i = contour_info.contour_start_index;
	while (i <= glyph->end_pts_of_contours[contour_index])
	{
		if (get_points(&i, glyph, contour_info, current_points) < 0)
			return (-1);
	}
	if (ft_vector_append(dest, current_points) != VECTOR_SUCCESS)
		return (-1);
	current_points->length = 0;
	return (0);
}

static int	get_points(uint32_t *i, const t_glyph_outline *glyph,
				const t_contour_info contour_info, t_vector *current_points)
{
	if (glyph->flags[*i].on_curve)
		return (handle_on_curve(current_points, glyph, i));
	return (handle_off_curve(current_points, glyph, i, contour_info));
}

static int	handle_on_curve(t_vector *current_points,
				const t_glyph_outline *glyph, uint32_t *i)
{
	t_vector2f	tmp[4];

	tmp[0] = (t_vector2f){glyph->x_coordinates[*i],
		glyph->y_coordinates[*i]};
	if (ft_vector_add_elem(current_points, tmp) != VECTOR_SUCCESS)
		return (-1);
	(*i)++;
	return (0);
}

static int	handle_off_curve(t_vector *current_points,
				const t_glyph_outline *glyph, uint32_t *i,
				const t_contour_info contour_info)
{
	t_vector2f	tmp[4];
	uint16_t	next_index;

	next_index = (*i + 1 - contour_info.contour_start_index)
		% contour_info.contour_len + contour_info.contour_start_index;
	if (current_points->length <= 0)
		return (-1);
	tmp[0] = ((t_vector2f *)current_points->data)[current_points->length - 1];
	tmp[1] = (t_vector2f){glyph->x_coordinates[*i], glyph->y_coordinates[*i]};
	tmp[2] = (t_vector2f){glyph->x_coordinates[next_index],
		glyph->y_coordinates[next_index]};
	if (glyph->flags[next_index].on_curve == true)
		(*i)++;
	else
		tmp[2] = vector2f_add(tmp[1],
				vector2f_divide(vector2f_subtract(tmp[2], tmp[1]), 2.f));
	if (get_quadratic_bezier_points(current_points, tmp,
			NB_OF_POINT_ON_CURVE_TO_GENERATE) < 0)
		return (-1);
	(*i)++;
	return (0);
}
