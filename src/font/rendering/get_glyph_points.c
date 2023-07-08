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

int	get_glyph_points(t_vector *dest, const t_glyph_outline *glyph,
		size_t **end_of_generated_contours)
{
	int16_t			contour_index;
	uint32_t		i;
	t_vector		current_points;
	t_vector2f		tmp[4];

	*end_of_generated_contours = malloc(sizeof(**end_of_generated_contours) * glyph->numberOfContours); // TODO secure
	ft_vector_create(dest, sizeof(t_vector2f), 0);
	ft_vector_create(&current_points, sizeof(t_vector2f), 0);
	contour_index = -1;
	while (++contour_index < glyph->numberOfContours)
	{
		uint16_t	contour_len;
		uint16_t	contour_start_index;
		if (contour_index == 0)
			contour_start_index = 0;
		else
			contour_start_index = glyph->endPtsOfContours[contour_index - 1] + 1;
		if (contour_index == 0)
			contour_len = glyph->endPtsOfContours[contour_index] + 1;
		else
			contour_len = glyph->endPtsOfContours[contour_index] - glyph->endPtsOfContours[contour_index - 1];
		i = contour_start_index;
		while (i <= glyph->endPtsOfContours[contour_index])
		{
			if (glyph->flags[i].on_curve)
			{
				tmp[0] = (t_vector2f){glyph->xCoordinates[i], glyph->yCoordinates[i]};
				ft_vector_add_elem(&current_points, tmp); // TODO secure
				i++;
				continue ;
			}
			uint16_t	next_index = (i + 1 - contour_start_index) % contour_len + contour_start_index;
			// TODO handle first coordinates being off curve
			tmp[0] = ((t_vector2f *)current_points.data)[current_points.length - 1];
			tmp[1] = (t_vector2f){glyph->xCoordinates[i], glyph->yCoordinates[i]};
			tmp[2] = (t_vector2f){glyph->xCoordinates[next_index], glyph->yCoordinates[next_index]};
			if (glyph->flags[next_index].on_curve == true)
				i++;
			else
				tmp[2] = vector2f_add(tmp[1], vector2f_divide(vector2f_subtract(tmp[2], tmp[1]), 2.f));
			get_quadratic_bezier_points(&current_points, tmp, NB_OF_POINT_ON_CURVE_TO_GENERATE); // TODO secure
			i++;
		}
		ft_vector_append(dest, &current_points); // TODO secure
		current_points.length = 0;
		(*end_of_generated_contours)[contour_index] = dest->length;
	}
	ft_vector_destroy(&current_points);
	return (0);
}
