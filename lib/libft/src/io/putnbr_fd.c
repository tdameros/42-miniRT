/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 20:44:25 by vfries            #+#    #+#             */
/*   Updated: 2023/04/09 00:20:09 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>

static int8_t	ft_putnbr_in_buf(long n, char *buf)
{
	int8_t	start;

	start = 11;
	while (n > 0)
	{
		buf[--start] = n % 10 + '0';
		n /= 10;
	}
	return (start);
}

ssize_t	ft_putnbr_fd(int n, int fd)
{
	char	buf[11];
	int8_t	start;

	if (n == 0)
		return (write(fd, "0", 1));
	else if (n < 0)
	{
		start = ft_putnbr_in_buf(-(long)n, buf);
		buf[--start] = '-';
	}
	else
		start = ft_putnbr_in_buf(n, buf);
	return (write(fd, buf + start, 11 - start));
}
