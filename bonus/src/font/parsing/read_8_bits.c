/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_8_bits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:39:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/26 22:39:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	read_uint8(const t_string *file, const size_t i, uint8_t *dest)
{
	const uint8_t	*read_address = (const uint8_t *)file->data + i;

	if (i + sizeof(uint8_t) > file->len)
		return (-1);
	*dest = read_address[0];
	return (0);
}

int	read_uint8_move(const t_string *file, size_t *i, uint8_t *dest)
{
	if (read_uint8(file, *i, dest) < 0)
		return (-1);
	*i += sizeof(uint8_t);
	return (0);
}

int	read_int8(const t_string *file, const size_t i, int8_t *dest)
{
	const uint8_t	*read_address = (const uint8_t *)file->data + i;

	if (i + sizeof(int8_t) > file->len)
		return (-1);
	*dest = (int8_t)read_address[0];
	return (0);
}

int	read_int8_move(const t_string *file, size_t *i, int8_t *dest)
{
	if (read_int8(file, *i, dest) < 0)
		return (-1);
	*i += sizeof(int8_t);
	return (0);
}
