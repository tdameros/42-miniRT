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
#ifndef TTF_H
# define TTF_H

# include <stdint.h>

# include "libft.h"

/// @typedef t_fixed is an unsigned 32 bit integer, the first 16 bits are used
/// for the whole part, the second part is used for the decimal part
typedef int32_t	t_fixed;

/// @typedef 16-bit signed integer that describes a quantity in FUnits, the
/// smallest measurable distance in em space.
typedef int16_t	t_fword;

/// @typedef 16-bit unsigned integer that describes a quantity in FUnits, the
/// smallest measurable distance in em space.
typedef int16_t	t_ufword;

/// @typedef The long internal format of a date in seconds since 12:00 midnight,
/// January 1, 1904. It is represented as a signed 64-bit integer.
typedef int64_t	t_long_date_time;

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

typedef struct s_glyph_outline
{
	int16_t					numberOfContours;
	t_fword					xMin;
	t_fword					yMin;
	t_fword					xMax;
	t_fword					yMax;
	uint16_t				*endPtsOfContours;
	uint16_t				instructionLength;
	uint8_t					*instructions;
	t_glyph_outline_flag	*flags;
	int16_t					*xCoordinates;
	int16_t					*yCoordinates;
}	t_glyph_outline;

typedef struct s_loca
{
	uint32_t			size;
	uint32_t			*offsets;
}	t_loca;

typedef struct s_maxp
{
	t_fixed		version;
	uint16_t	numGlyphs;
	uint16_t	maxPoints;
	uint16_t	maxContours;
	uint16_t	maxComponentPoints;
	uint16_t	maxComponentContours;
	uint16_t	maxZones;
	uint16_t	maxTwilightPoints;
	uint16_t	maxStorage;
	uint16_t	maxFunctionDefs;
	uint16_t	maxInstructionDefs;
	uint16_t	maxStackElements;
	uint16_t	maxSizeOfInstructions;
	uint16_t	maxComponentElements;
	uint16_t	maxComponentDepth;
}	t_maxp;

typedef struct s_head
{
	t_fixed				version;
	t_fixed				fontRevision;
	uint32_t			checkSumAdjustment;
	uint32_t			magicNumber;
	uint16_t			flags;
	uint16_t			unitsPerEm;
	t_long_date_time	created;
	t_long_date_time	modified;
	t_fword				xMin;
	t_fword				yMin;
	t_fword				xMax;
	t_fword				yMax;
	uint16_t			macStyle;
	uint16_t			lowestRecPPEM;
	int16_t				fontDirectionHint;
	int16_t				indexToLocFormat;
	int16_t				glyphDataFormat;
}	t_head;

typedef struct s_format4
{
	uint16_t	format;
	uint16_t	length;
	uint16_t	language;
	uint16_t	segCountX2;
	uint16_t	searchRange;
	uint16_t	entrySelector;
	uint16_t	rangeShift;
	uint16_t	*endCode;
	uint16_t	reservedPad;
	uint16_t	*startCode;
	uint16_t	*idDelta;
	uint16_t	*idRangeOffset;
	uint16_t	*glyphIdArray;
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
/// number that identifies the font type
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
}	t_ttf;

typedef struct s_font
{
	t_ttf			ttf;
	size_t			glyphs_count;
	t_glyph_outline	*glyphs;
}	t_font;

int				ttf_parser(t_font *font, char *file_name);

int				read_font_directory(const t_string *file,
					t_font_directory *font_directory);
int				read_cmap(const t_string *file, t_ttf *ttf);
int				read_format4(const t_string *file, t_ttf *ttf);
int				read_head(const t_string *file, t_ttf *ttf);
int				read_maxp(const t_string *file, t_ttf *ttf);
int				read_loca(const t_string *file, t_ttf *ttf);
int				read_x_coordinates(const t_string *file, size_t *file_cursor,
					t_glyph_outline *outline, uint16_t last_index);
int				read_y_coordinates(const t_string *file, size_t *file_cursor,
					t_glyph_outline *outline, uint16_t last_index);

int64_t			ttf_get_table_offset(const t_ttf *ttf, const char *table_name);
uint32_t		get_glyph_offset(uint32_t glyph_index, const t_ttf *ttf);
uint32_t		get_glyph_index(uint16_t code_point, const t_ttf *ttf);
int				read_glyph_outline(const t_string *file, size_t offset,
					t_glyph_outline *outline);
t_glyph_outline	*get_glyph_outlines(const t_string *file, t_ttf *ttf);

int				read_uint8(const t_string *file, size_t i, uint8_t *dest);
int				read_uint8_move(const t_string *file, size_t *i, uint8_t *dest);
int				read_int8(const t_string *file, size_t i, int8_t *dest);
int				read_int8_move(const t_string *file, size_t *i, int8_t *dest);

int				read_uint16(const t_string *file, size_t i, uint16_t *dest);
int				read_uint16_move(const t_string *file, size_t *i,
					uint16_t *dest);
uint16_t		read_uint16_unsafe(const char *str);
int				read_int16(const t_string *file, size_t i, int16_t *dest);
int				read_int16_move(const t_string *file, size_t *i, int16_t *dest);

int				read_uint32(const t_string *file, size_t i, uint32_t *dest);
int				read_uint32_move(const t_string *file, size_t *i,
					uint32_t *dest);
uint32_t		read_uint32_unsafe(const char *str);
int				read_int32(const t_string *file, size_t i, int32_t *dest);
int				read_int32_move(const t_string *file, size_t *i, int32_t *dest);

int				read_int64(const t_string *file, size_t i, int64_t *dest);
int				read_int64_move(const t_string *file, size_t *i, int64_t *dest);

#endif
