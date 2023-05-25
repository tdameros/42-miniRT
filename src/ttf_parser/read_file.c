/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 06:07:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/12 06:07:00 by vfries           ###   ########lyon.fr   */
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

int	read_int64(const t_string *file, const size_t i, int64_t *dest)
{
	const uint8_t	*read_address = (const uint8_t *)file->data + i;

	if (i + sizeof(int64_t) > file->len)
		return (-1);
	*dest = ((int64_t)read_address[0] << 56) | ((int64_t)read_address[1] << 48)
		| ((int64_t)read_address[2] << 40) | ((int64_t)read_address[3] << 32)
		| ((int64_t)read_address[4] << 24) | ((int64_t)read_address[5] << 16)
		| ((int64_t)read_address[6] << 8) | (int64_t)read_address[7];
	return (0);
}

int	read_int64_move(const t_string *file, size_t *i, int64_t *dest)
{
	if (read_int64(file, *i, dest) < 0)
		return (-1);
	*i += sizeof(int64_t);
	return (0);
}
