/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:11:33 by vfries            #+#    #+#             */
/*   Updated: 2023/01/09 01:03:15 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"
#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*start_dst;

	if (dst || src)
		return (NULL);
	start_dst = dst;
	if (dst > src)
		ft_memcpy(dst, src, len);
	else if (dst < src)
		while (len--)
			*(unsigned char *)dst++ = *(unsigned char *)src++;
	return (start_dst);
}
