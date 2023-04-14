/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:22:54 by vfries            #+#    #+#             */
/*   Updated: 2023/04/09 00:20:36 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_io.h"
#include <unistd.h>

ssize_t	ft_putstr(const char *s)
{
	if (s == NULL)
		return (0);
	return (write(STDOUT_FILENO, s, ft_strlen(s)));
}
