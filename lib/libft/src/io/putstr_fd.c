/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 20:39:01 by vfries            #+#    #+#             */
/*   Updated: 2023/04/09 00:20:25 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <unistd.h>

ssize_t	ft_putstr_fd(const char *s, int fd)
{
	if (s == NULL)
		return (0);
	return (write(fd, s, ft_strlen(s)));
}
