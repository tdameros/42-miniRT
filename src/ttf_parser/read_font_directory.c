/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_font_directory.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 06:34:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/12 06:34:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "ttf.h"

static int	read_offset_subtable(const t_string *file, size_t *i,
				t_offset_subtable *offset_subtable);
static int	read_table_directory(const t_string *file, size_t *i,
				t_table_directory **table_directory, uint16_t number_of_tables);
static int	error_in_read_table_directory(t_table_directory **table_directory);

int	read_font_directory(const t_string *file, t_font_directory *font_directory)
{
	size_t	i;

	i = 0;
	if (read_offset_subtable(file, &i, &font_directory->offset_subtable) < 0)
		return (-1);
	if (font_directory->offset_subtable.scaler_type != 0x74727565
		&& font_directory->offset_subtable.scaler_type != 0x00010000)
	{
		ft_putstr_fd("Unexpected font format, expected TrueType\n",
			STDERR_FILENO);
		ft_bzero(font_directory, sizeof(*font_directory));
		return (-1);
	}
	if (read_table_directory(file, &i, &font_directory->table_directory,
			font_directory->offset_subtable.num_tables) < 0)
		return (-1);
	return (0);
}

static int	read_offset_subtable(const t_string *file, size_t *i,
				t_offset_subtable *offset_subtable)
{
	if (read_uint32_move(file, i, &offset_subtable->scaler_type) < 0)
		return (-1);
	if (read_uint16_move(file, i, &offset_subtable->num_tables) < 0)
		return (-1);
	if (read_uint16_move(file, i, &offset_subtable->search_range) < 0)
		return (-1);
	if (read_uint16_move(file, i, &offset_subtable->entry_selector) < 0)
		return (-1);
	if (read_uint16_move(file, i, &offset_subtable->range_shift) < 0)
		return (-1);
	return (0);
}

static int	read_table_directory(const t_string *file, size_t *i,
				t_table_directory **table_directory, uint16_t number_of_tables)
{
	uint16_t			j;
	t_table_directory	*current_table_directory;

	*table_directory = ft_calloc(number_of_tables, sizeof(**table_directory));
	if (*table_directory == NULL)
		return (-1);
	j = -1;
	while (++j < number_of_tables)
	{
		current_table_directory = *table_directory + j;
		if (read_uint32_move(file, i, &current_table_directory->tag) < 0)
			return (error_in_read_table_directory(table_directory));
		if (read_uint32_move(file, i, &current_table_directory->check_sum) < 0)
			return (error_in_read_table_directory(table_directory));
		if (read_uint32_move(file, i, &current_table_directory->offset) < 0)
			return (error_in_read_table_directory(table_directory));
		if (read_uint32_move(file, i, &current_table_directory->length) < 0)
			return (error_in_read_table_directory(table_directory));
	}
	return (0);
}

static int	error_in_read_table_directory(t_table_directory **table_directory)
{
	free(*table_directory);
	*table_directory = NULL;
	return (-1);
}
