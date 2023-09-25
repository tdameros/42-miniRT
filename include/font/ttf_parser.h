/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 03:28:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/12 03:28:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef TTF_PARSER_H
# define TTF_PARSER_H

# include <stdint.h>

# include "libft.h"

/// @typedef t_fixed is an unsigned 32 bit integer, the first 16 bits are used
/// for the whole part, the second part is used for the decimal part
typedef uint32_t	t_fixed;

/// @typedef 16-bit signed integer that describes a quantity in FUnits, the
/// smallest measurable distance in em space.
typedef int16_t		t_fword;

/// @typedef 16-bit unsigned integer that describes a quantity in FUnits, the
/// smallest measurable distance in em space.
typedef uint16_t	t_ufword;

/// @typedef The long internal format of a date in seconds since 12:00 midnight,
/// January 1, 1904. It is represented as a signed 64-bit integer.
typedef int64_t		t_long_date_time;

typedef struct s_long_hor_metric
{
	uint16_t	advance_width;
	int16_t		left_side_bearing;
}	t_long_hor_metric;

typedef struct s_hmtx
{
	t_long_hor_metric	*h_metrics;
	t_fword				*left_side_bearing;
}	t_hmtx;

typedef struct s_hhea
{
	t_fixed		version;
	t_fword		ascent;
	t_fword		descent;
	t_fword		line_gap;
	t_ufword	advance_width_max;
	t_fword		min_left_side_bearing;
	t_fword		min_right_side_bearing;
	t_fword		x_max_extent;
	int16_t		caret_slope_rise;
	int16_t		caret_slope_run;
	t_fword		caret_offset;
	int16_t		metric_data_format;
	uint16_t	num_of_long_hor_metrics;
}	t_hhea;

typedef union u_glyph_outline_flag
{
	struct
	{
		uint8_t	on_curve: 1;
		uint8_t	x_short: 1;
		uint8_t	y_short: 1;
		uint8_t	repeat: 1;
		uint8_t	x_short_pos: 1;
		uint8_t	y_short_pos: 1;
		uint8_t	reserved1: 1;
		uint8_t	reserved2: 1;
	};
	uint8_t	flag;
}	t_glyph_outline_flag;

typedef struct s_glyph_outline_bounds
{
	t_fword					x_min;
	t_fword					y_min;
	t_fword					x_max;
	t_fword					y_max;
}	t_glyph_outline_bounds;

typedef struct s_glyph_outline
{
	int16_t					number_of_contours;
	t_glyph_outline_bounds	bounds;
	uint16_t				*end_pts_of_contours;
	uint16_t				instruction_length;
	uint8_t					*instructions;
	t_glyph_outline_flag	*flags;
	int16_t					*x_coordinates;
	int16_t					*y_coordinates;
}	t_glyph_outline;

typedef struct s_loca
{
	uint32_t			size;
	uint32_t			*offsets;
}	t_loca;

typedef struct s_maxp
{
	t_fixed		version;
	uint16_t	num_glyphs;
	uint16_t	max_points;
	uint16_t	max_contours;
	uint16_t	max_component_points;
	uint16_t	max_component_contours;
	uint16_t	max_zones;
	uint16_t	max_twilight_points;
	uint16_t	max_storage;
	uint16_t	max_function_defs;
	uint16_t	max_instruction_defs;
	uint16_t	max_stack_elements;
	uint16_t	max_size_of_instructions;
	uint16_t	max_component_elements;
	uint16_t	max_component_depth;
}	t_maxp;

typedef struct s_head
{
	t_fixed				version;
	t_fixed				font_revision;
	uint32_t			check_sum_adjustment;
	uint32_t			magic_number;
	uint16_t			flags;
	uint16_t			units_per_em;
	t_long_date_time	created;
	t_long_date_time	modified;
	t_fword				x_min;
	t_fword				y_min;
	t_fword				x_max;
	t_fword				y_max;
	uint16_t			mac_style;
	uint16_t			lowest_eec_ppem;
	int16_t				font_direction_hint;
	int16_t				index_to_loc_format;
	int16_t				glyph_data_format;
}	t_head;

typedef struct s_format4
{
	uint16_t	format;
	uint16_t	length;
	uint16_t	language;
	uint16_t	seg_count_x2;
	uint16_t	search_range;
	uint16_t	entry_selector;
	uint16_t	range_shift;
	uint16_t	*end_code;
	uint16_t	reserved_pad;
	uint16_t	*start_code;
	uint16_t	*id_delta;
	uint16_t	*id_range_offset;
	uint16_t	*glyph_id_array;
}	t_format4;

/// @struct s_offset_subtable
/// @var ::platform_id
/// identifies the platform for which the encoding subtable is intended
/// @var ::platform_specific_id
/// identifies the encoding subtable within the context of the platform
/// specified by platform_id
/// @var ::offset
/// gives the offset from the beginning of the cmap to the start of the encoding
/// subtable
typedef struct s_cmap_encoding_subtable
{
	uint16_t	platform_id;
	uint16_t	platform_specific_id;
	uint32_t	offset;
}	t_cmap_encoding_subtable;

/// @struct s_offset_subtable
/// @var ::version
/// specifies the version number of the cmap format
/// @var ::number_subtables
/// specifies the number of encoding subtables present in the cmap
/// @var ::subtables
/// array of t_cmap_encoding_subtable structures that represent the encoding
/// subtables in the cmap
typedef struct s_cmap
{
	uint16_t					version;
	uint16_t					number_subtables;
	t_cmap_encoding_subtable	*subtables;
}	t_cmap;

/// @struct s_offset_subtable
/// @var ::scaler_type
/// number that identifies the font surface_type
/// @var ::num_tables
/// contains the number of tables excluding the table_directory and any
/// subtables
/// @var ::search_range
/// (maximum power of 2 &lt;= num_tables) * 16 ___
/// (16 represents the size of a directory entry)
/// @var ::entry_selector
/// log2(search_range / 16)
/// @var ::range_shift
/// num_tables * 16 - search_range
typedef struct s_offset_subtable
{
	uint32_t	scaler_type;
	uint16_t	num_tables;
	uint16_t	search_range;
	uint16_t	entry_selector;
	uint16_t	range_shift;
}	t_offset_subtable;

typedef struct s_table_directory
{
	union {
		char		tag_c[4];
		uint32_t	tag;
	};
	uint32_t	check_sum;
	uint32_t	offset;
	uint32_t	length;
}	t_table_directory;

typedef struct s_ttf_font_directory
{
	t_offset_subtable	offset_subtable;
	t_table_directory	*table_directory;
}	t_font_directory;

typedef struct s_ttf
{
	t_font_directory	font_directory;
	uint32_t			cmap_offset;
	t_cmap				cmap;
	uint32_t			format4_offset;
	t_format4			*format4;
	t_head				head;
	t_maxp				maxp;
	t_loca				loca;
	t_hhea				hhea;
	t_hmtx				hmtx;
	size_t				glyphs_count;
	t_glyph_outline		*glyphs;
}	t_ttf;

//	get_glyph_offset.c
uint32_t			get_glyph_offset(uint32_t glyph_index, const t_ttf *ttf);
uint32_t			get_glyph_index(uint16_t code_point, const t_ttf *ttf);

//	get_glyph_outlines.c
t_glyph_outline		*get_glyph_outlines(const t_string *file, t_ttf *ttf);

//	get_long_hor_metric.c
t_long_hor_metric	get_long_hor_metric(uint16_t glyph_index, const t_ttf *ttf);

//	read_8_bits.c
int					read_uint8(const t_string *file, size_t i, uint8_t *dest);
int					read_uint8_move(const t_string *file, size_t *i,
						uint8_t *dest);
int					read_int8(const t_string *file, size_t i, int8_t *dest);
int					read_int8_move(const t_string *file, size_t *i,
						int8_t *dest);

//	read_16_bits.c
int					read_uint16(const t_string *file, size_t i, uint16_t *dest);
int					read_uint16_move(const t_string *file, size_t *i,
						uint16_t *dest);
uint16_t			read_uint16_unsafe(const char *str);
int					read_int16(const t_string *file, size_t i, int16_t *dest);
int					read_int16_move(const t_string *file, size_t *i,
						int16_t *dest);

//	read_32_bits.c
int					read_uint32(const t_string *file, size_t i, uint32_t *dest);
int					read_uint32_move(const t_string *file, size_t *i,
						uint32_t *dest);
uint32_t			read_uint32_unsafe(const char *str);
int					read_int32(const t_string *file, size_t i, int32_t *dest);
int					read_int32_move(const t_string *file, size_t *i,
						int32_t *dest);

//	read_64_bits.c
int					read_int64(const t_string *file, size_t i, int64_t *dest);
int					read_int64_move(const t_string *file, size_t *i,
						int64_t *dest);

//	read_cmap.c
int					read_cmap(const t_string *file, t_ttf *ttf);

//	read_font_directory.c
int					read_font_directory(const t_string *file,
						t_font_directory *font_directory);

//	read_format4.c
int					read_format4(const t_string *file, t_ttf *ttf);

//	read_glyph_outline.c
int					read_glyph_outline(const t_string *file, size_t offset,
						t_glyph_outline *outline);

//	read_glyph_outline_coordinates.c
int					read_x_coordinates(const t_string *file,
						size_t *file_cursor, t_glyph_outline *outline,
						uint16_t last_index);
int					read_y_coordinates(const t_string *file,
						size_t *file_cursor, t_glyph_outline *outline,
						uint16_t last_index);

//	read_head.c
int					read_head(const t_string *file, t_ttf *ttf);

//	read_hhea.c
int					read_hhea(const t_string *file, t_ttf *ttf);

//	read_hmtx.c
int					read_hmtx(const t_string *file, t_ttf *ttf);

//	read_loca.c
int					read_loca(const t_string *file, t_ttf *ttf);

//	read_maxp.c
int					read_maxp(const t_string *file, t_ttf *ttf);

//	ttf_get_table_offset.c
int64_t				ttf_get_table_offset(const t_ttf *ttf,
						const char *table_name);

//	ttf_parser.c
int					ttf_parser(t_ttf *font, char *file_name);
void				destroy_t_ttf(t_ttf *ttf);

#endif
