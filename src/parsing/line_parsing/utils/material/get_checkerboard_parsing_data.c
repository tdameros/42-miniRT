/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_checkerboard_parsing_data.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 11:05:25 by vfries            #+#    #+#             */
/*   Updated: 2023/09/03 11:05:26 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <math.h>

#include "parsing.h"

static void			get_checkerboard_size(char *size, t_vector2f *dest);
static t_color		get_checkerboard_color(char *color);

t_checkerboard_parsing_data	get_checkerboard_parsing_data(
								char *raw_checkerboard_data)
{
	t_checkerboard_parsing_data	result;
	char						**checkerboard_data_split;

	checkerboard_data_split = ft_split(raw_checkerboard_data, '-');
	if (checkerboard_data_split == NULL
		|| ft_split_len(checkerboard_data_split) != 2)
	{
		ft_print_error("Warning: failed to parse checkerboard data ");
		ft_print_error(raw_checkerboard_data);
		ft_print_error("\n");
		return ((t_checkerboard_parsing_data){0});
	}
	get_checkerboard_size(checkerboard_data_split[0], &result.size);
	result.color = get_checkerboard_color(checkerboard_data_split[1]);
	return (result);
}

static void	get_checkerboard_size(char *size, t_vector2f *dest)
{
	char	**size_split;

	size_split = ft_split(size, ',');
	if (size_split == NULL || ft_split_len(size_split) != 2)
	{
		ft_print_error("Warning: failed to parse checkerboard size ");
		ft_print_error(size);
		ft_print_error("\n");
		*dest = (t_vector2f){0.f, 0.f};
		return (ft_free_split(size_split));
	}
	errno = 0;
	dest->x = ft_atof(size_split[0]);
	dest->y = ft_atof(size_split[1]);
	if (dest->x < 0.f || dest->y < 0.f || (int)dest->x % 2 || (int)dest->y % 2)
	{
		ft_print_error("Warning: abnormal checkerboard size in rt file ");
		ft_print_error(size);
		ft_print_error(" should be positive integers that are divisible by 2"
			"\n");
	}
	dest->x = fmaxf(0.f, dest->x + (int)dest->x % 2);
	dest->y = fmaxf(0.f, dest->y + (int)dest->y % 2);
	errno = 0;
	ft_free_split(size_split);
}

static t_color	get_checkerboard_color(char *color)
{
	t_color	result;

	if (get_color(color, &result) < 0)
	{
		ft_print_error("Warning: abnormal checkerboard color in rt file ");
		ft_print_error(color);
		ft_print_error(" should be floats >= 0 and <= 255\n");
		return ((t_color){0, 0, 0});
	}
	return (result);
}
