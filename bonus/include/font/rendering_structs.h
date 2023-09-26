/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 02:16:00 by vfries            #+#    #+#             */
/*   Updated: 2023/09/25 21:56:50 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_STRUCTS_H
# define RENDERING_STRUCTS_H

# include "font/ttf_parser.h"
# include "math/vector.h"

# define NUMBER_OF_GLYPHS 127

typedef struct s_triangle
{
	t_vector2f	a;
	t_vector2f	b;
	t_vector2f	c;
}	t_triangle;

typedef struct s_triangles
{
	t_triangle	*data;
	size_t		size;
}	t_triangles;

typedef struct s_segment
{
	t_vector2f	a;
	t_vector2f	b;
}	t_segment;

typedef struct s_glyph_generated_points
{
	t_vector2f				*points;
	size_t					nb_of_points;
	size_t					*contours_limits;
	int16_t					nb_of_contours;
	t_glyph_outline_bounds	bounds;
}	t_glyph_generated_points;

typedef struct s_font
{
	t_glyph_generated_points	*glyphs;
	t_long_hor_metric			*long_hor_metric;
	t_glyph_outline_bounds		bounds;
}	t_font;

#endif
