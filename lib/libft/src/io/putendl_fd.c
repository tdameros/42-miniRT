/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putendl_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 20:41:36 by vfries            #+#    #+#             */
/*   Updated: 2023/04/09 00:19:46 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <unistd.h>

ssize_t	ft_putendl_fd(const char *s, int fd)
{
	ssize_t	tmp;

	if (s == NULL)
		return (0);
	tmp = write(fd, s, ft_strlen(s));
	if (tmp < 0 || write(fd, "\n", 1) < 0)
		return (-1);
	return (tmp + 1);
}
