/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_16_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:40:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/26 22:40:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	read_uint16(const t_string *file, const size_t i, uint16_t *dest)
{
	const uint8_t	*read_address = (const uint8_t *)file->data + i;

	if (i + sizeof(uint16_t) > file->len)
		return (-1);
	*dest = ((uint16_t)read_address[0] << 8) | (uint16_t)read_address[1];
	return (0);
}

int	read_uint16_move(const t_string *file, size_t *i, uint16_t *dest)
{
	if (read_uint16(file, *i, dest) < 0)
		return (-1);
	*i += sizeof(uint16_t);
	return (0);
}

uint16_t	read_uint16_unsafe(const char *str)
{
	const uint8_t	*read_address = (const uint8_t *)str;

	return (((uint16_t)read_address[0] << 8) | (uint16_t)read_address[1]);
}

int	read_int16(const t_string *file, const size_t i, int16_t *dest)
{
	const uint8_t	*read_address = (const uint8_t *)file->data + i;

	if (i + sizeof(int16_t) > file->len)
		return (-1);
	*dest = ((int16_t)read_address[0] << 8) | (int16_t)read_address[1];
	return (0);
}

int	read_int16_move(const t_string *file, size_t *i, int16_t *dest)
{
	if (read_int16(file, *i, dest) < 0)
		return (-1);
	*i += sizeof(int16_t);
	return (0);
}
