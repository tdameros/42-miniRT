/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttf_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 03:26:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/12 03:26:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "ttf.h"

#include <stdio.h>

static int	error_in_ttf_parser(t_string *file, t_ttf *ttf);
static void	destroy_t_ttf(t_ttf *ttf);

void	print_table_directory(const t_table_directory *tbl_dir, int tbl_size);
void	print_cmap(const t_cmap *c);
void	print_format4(const t_format4 *f4);
void 	print_head(const t_head *head);
void 	print_maxp(t_maxp *maxp);
void	print_loca(t_loca *loca);
void 	print_glyph_outline(t_glyph_outline *outline);

int	ttf_parser(t_font *font, char *file_name)
{
	t_string	file;
	// TODO improve error messages

	file = ft_read_file(file_name);
	if (file.data == NULL)
	{
		perror("ttf_parser failed");
		return (-1);
	}
	font->ttf = (t_ttf){0};
	if (read_font_directory(&file, &font->ttf.font_directory) < 0)
	{
		ft_print_error("Failed to parse font directory\n");
		return (error_in_ttf_parser(&file, &font->ttf));
	}
	print_table_directory(font->ttf.font_directory.table_directory,
		font->ttf.font_directory.offset_subtable.num_tables); // Testing
	if (read_cmap(&file, &font->ttf) < 0)
	{
		ft_print_error("Bad read_cmap()\n");
		return (error_in_ttf_parser(&file, &font->ttf));
	}
	print_cmap(&font->ttf.cmap); // Testing
	if (read_format4(&file, &font->ttf) < 0)
	{
		ft_print_error("Failed to read format4\n");
		return (error_in_ttf_parser(&file, &font->ttf));
	}
	print_format4(font->ttf.format4); // Testing
	if (read_head(&file, &font->ttf) < 0)
	{
		ft_print_error("Failed to read head\n");
		return (error_in_ttf_parser(&file, &font->ttf));
	}
	print_head(&font->ttf.head); // Testing
	if (read_maxp(&file, &font->ttf) < 0)
	{
		ft_print_error("Failed to read maxp\n");
		return (error_in_ttf_parser(&file, &font->ttf));
	}
	print_maxp(&font->ttf.maxp); // Testing
	if (read_loca(&file, &font->ttf) < 0)
	{
		ft_print_error("Failed to read loca\n");
		return (error_in_ttf_parser(&file, &font->ttf));
	}
	print_loca(&font->ttf.loca); // Testing

	font->glyphs = get_glyph_outlines(&file, &font->ttf);
	if (font->glyphs == NULL)
		return (error_in_ttf_parser(&file, &font->ttf));
	font->glyphs_count = font->ttf.maxp.numGlyphs;
	free(file.data);

	// Testing
	char c = 0;
	while (c >= 0)
	{
		uint32_t index = get_glyph_index(c, &font->ttf);
		printf("%c / %u index == %i\n", c, c, index);
		print_glyph_outline(font->glyphs + index);
		c++;
	}
	//!Testing

	return (0);
}

static int	error_in_ttf_parser(t_string *file, t_ttf *ttf)
{
	free(file->data);
	destroy_t_ttf(ttf);
	return (-1);
}

static void	destroy_t_ttf(t_ttf *ttf)
{
	free(ttf->font_directory.table_directory);
	free(ttf->cmap.subtables);
	free(ttf->format4);
	free(ttf->loca.offsets);
}

void print_table_directory(const t_table_directory* tbl_dir, int tbl_size)
{
	//TODO remove this function
	printf("\ntable_directory:\n#)\ttag\tlen\toffset\n");
	for (int i = 0; i < tbl_size; ++i)
	{
		const t_table_directory* t = tbl_dir + i;
		printf("%d)\t%c%c%c%c\t%u\t%u\n", i + 1,
			t->tag_c[3], t->tag_c[2],
			t->tag_c[1], t->tag_c[0],
			t->length, t->offset);
	}
}

void print_cmap(const t_cmap* c)
{
	printf("\ncmap:\n#)\tpId\tpsID\toffset\ttype\n");
	for(int i = 0; i < c->number_subtables; ++i)
	{
		t_cmap_encoding_subtable* cet = c->subtables + i;
		printf("%d)\t%hu\t%hu\t%i\t", i+1, cet->platform_id, cet->platform_specific_id, cet->offset);
		switch(cet->platform_id)
		{
			case 0: printf("Unicode"); break;
			case 1: printf("Mac"); break;
			case 2: printf("Not Supported"); break;
			case 3: printf("Microsoft"); break;
		}
		printf("\n");
	}
}

void print_format4(const t_format4 *f4)
{
	printf("Format: %d, Length: %d, Language: %d, Segment Count: %d\n", f4->format, f4->length, f4->language, f4->segCountX2/2);
	printf("Search Params: (searchRange: %d, entrySelector: %d, rangeShift: %d)\n",
		   f4->searchRange, f4->entrySelector, f4->rangeShift);
	printf("Segment Ranges:\tstartCode\tendCode\tidDelta\tidRangeOffset\n");
	for(int i = 0; i < f4->segCountX2/2; ++i) {
		printf("--------------:\t% 9d\t% 7d\t% 7d\t% 12d\n", f4->startCode[i], f4->endCode[i], f4->idDelta[i], f4->idRangeOffset[i]);
	}
}

void	t_fixed_print(const t_fixed f)
{
	printf("%f\n", (float)f /  65536.f);
}

void	t_long_date_time_print(const t_long_date_time long_date_time)
{
	const time_t	unix_time = long_date_time - 2082844800;
	struct tm		*time_info;

	time_info = gmtime(&unix_time);
	printf("Date: %02d-%02d-%04d\n", time_info->tm_mday, time_info->tm_mon + 1, time_info->tm_year + 1900);
}

void print_head(const t_head *head)
{
	printf("\nhead:\n");
	printf("\tversion: ");
	t_fixed_print(head->version);
	printf("\tfontRevision: ");
	t_fixed_print(head->fontRevision);
	printf("\tcheckSumAdjustment: %u\n", head->checkSumAdjustment);
	printf("\tmagicNumber: %u\n", head->magicNumber);
	printf("\tflags: %u\n", head->flags);
	printf("\tunitsPerEm: %u\n", head->unitsPerEm);
	printf("\tcreated: ");
	t_long_date_time_print(head->created);
	printf("\tmodified: ");
	t_long_date_time_print(head->modified);
	printf("\txMin: %d\n", head->xMin);
	printf("\tyMin: %d\n", head->yMin);
	printf("\txMax: %d\n", head->xMax);
	printf("\tyMax: %d\n", head->yMax);
	printf("\tmacStyle: %u\n", head->macStyle);
	printf("\tlowestRecPPEM: %u\n", head->lowestRecPPEM);
	printf("\tfontDirectionHint: %d\n", head->fontDirectionHint);
	printf("\tindexToLocFormat: %d\n", head->indexToLocFormat);
	printf("\tglyphDataFormat: %d\n", head->glyphDataFormat);
}

void print_maxp(t_maxp *maxp)
{
	printf("\nmaxp:\n");
	printf("\tversion: ");
	t_fixed_print(maxp->version);
	printf("\tnumGlyphs: %u\n", maxp->numGlyphs);
	printf("\tmaxPoints: %u\n", maxp->maxPoints);
	printf("\tmaxContours: %u\n", maxp->maxContours);
	printf("\tmaxCompositePoints: %u\n", maxp->maxComponentPoints);
	printf("\tmaxCompositeContours: %u\n", maxp->maxComponentContours);
	printf("\tmaxZones: %u\n", maxp->maxZones);
	printf("\tmaxTwilightPoints: %u\n", maxp->maxTwilightPoints);
	printf("\tmaxStorage: %u\n", maxp->maxStorage);
	printf("\tmaxFunctionDefs: %u\n", maxp->maxFunctionDefs);
	printf("\tmaxInstructionDefs: %u\n", maxp->maxInstructionDefs);
	printf("\tmaxStackElements: %u\n", maxp->maxStackElements);
	printf("\tmaxSizeOfInstructions: %u\n", maxp->maxSizeOfInstructions);
	printf("\tmaxComponentElements: %u\n", maxp->maxComponentElements);
	printf("\tmaxComponentDepth: %u\n", maxp->maxComponentDepth);
}

void	print_loca(t_loca *loca)
{
	printf("\nloca:\n");
	for (size_t i = 0; i < loca->size; i++)
	{
		printf("\t index %zu, offset %u\n", i, loca->offsets[i]);
	}
}

void print_glyph_outline(t_glyph_outline *outline)
{
	if (outline->numberOfContours == 0)
	{
		printf("No outline\n");
		return ;
	}
	if (outline->numberOfContours < 0)
	{
		printf("Compound glyf\n");
		return ;
	}
	printf("#contours\t(xMin,yMin)\t(xMax,yMax)\tinst_length\n");
	printf("%9d\t(%d,%d)\t\t(%d,%d)\t%d\n", outline->numberOfContours,
		   outline->xMin, outline->yMin,
		   outline->xMax, outline->yMax,
		   outline->instructionLength);

	printf("#)\t(  x  ,  y  )\n");
	int last_index = outline->endPtsOfContours[outline->numberOfContours-1];
	for(int i = 0; i <= last_index; ++i) {
		printf("%d)\t(%5d,%5d)\n", i, outline->xCoordinates[i], outline->yCoordinates[i]);
	}
}
