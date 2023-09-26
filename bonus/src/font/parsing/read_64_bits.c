/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_64_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 06:07:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/12 06:07:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
