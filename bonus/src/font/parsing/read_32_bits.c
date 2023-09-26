/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_32_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:41:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/26 22:41:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	read_uint32(const t_string *file, const size_t i, uint32_t *dest)
{
	const uint8_t	*read_address = (const uint8_t *)file->data + i;

	if (i + sizeof(uint32_t) > file->len)
		return (-1);
	*dest = ((uint32_t)read_address[0] << 24)
		| ((uint32_t)read_address[1] << 16) | ((uint32_t)read_address[2] << 8)
		| (uint32_t)read_address[3];
	return (0);
}

int	read_uint32_move(const t_string *file, size_t *i, uint32_t *dest)
{
	if (read_uint32(file, *i, dest) < 0)
		return (-1);
	*i += sizeof(uint32_t);
	return (0);
}

uint32_t	read_uint32_unsafe(const char *str)
{
	const uint8_t	*read_address = (const uint8_t *)str;

	return (((uint32_t)read_address[0] << 24)
		| ((uint32_t)read_address[1] << 16) | ((uint32_t)read_address[2] << 8)
		| (uint32_t)read_address[3]);
}

int	read_int32(const t_string *file, const size_t i, int32_t *dest)
{
	const uint8_t	*read_address = (const uint8_t *)file->data + i;

	if (i + sizeof(int32_t) > file->len)
		return (-1);
	*dest = ((int32_t)read_address[0] << 24) | ((int32_t)read_address[1] << 16)
		| ((int32_t)read_address[2] << 8) | (int32_t)read_address[3];
	return (0);
}

int	read_int32_move(const t_string *file, size_t *i, int32_t *dest)
{
	if (read_int32(file, *i, dest) < 0)
		return (-1);
	*i += sizeof(int32_t);
	return (0);
}
