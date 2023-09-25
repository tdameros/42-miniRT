/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 01:51:00 by vfries            #+#    #+#             */
/*   Updated: 2023/09/24 01:44:58 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <stddef.h>

# include "engine.h"
# include "math/vector.h"
# include "font/ttf_parser.h"
# include "font/rendering_structs.h"
# include "image.h"

typedef struct s_draw_glyph_data
{
	const float			scale;
	t_image				*image;
	const unsigned int	color;
	const float			x_offset;
	const float			y_offset;
}	t_draw_glyph_data;

typedef struct s_contour_info
{
	uint16_t	contour_start_index;
	uint16_t	contour_len;
}	t_contour_info;

typedef struct s_write_character_data
{
	float		scale;
	t_vector2f	*offsets;
	bool		*is_decimal;
}	t_write_character_data;

//	do_segments_intersect.c
bool		do_segments_intersect(t_vector2f a, t_vector2f b, t_vector2f c,
				t_vector2f d);

//	draw_glyph.c
void		draw_glyph(const t_glyph_generated_points *raw_points,
				t_draw_glyph_data data);

//	get_glyph_points.c
int			get_glyph_points(t_vector *dest, const t_glyph_outline *glyph,
				size_t **end_of_generated_contours);

//	get_quadratic_bezier_points.c
int			get_quadratic_bezier_points(t_vector *dest,
				const t_vector2f *points, size_t number_of_points);

//	is_point_inside_glyph.c
bool		is_point_inside_glyph(t_vector2f point,
				const t_glyph_generated_points *points);

//	write_centered_number_to_image.c
void		write_centered_number_to_image(const t_font *font, t_image *image,
				const char *number);

//	write_centered_string_to_image.c
void		write_centered_string_to_image(const t_font *font, t_image *image,
				const char *string);

//	get_font.c
int			get_font(t_font *font, char *font_file);

#endif
