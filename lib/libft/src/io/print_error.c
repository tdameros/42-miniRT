/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:06:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/19 19:06:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"

ssize_t	ft_print_error(const char *str)
{
	if (str == NULL)
		return (write(STDERR_FILENO, "(null)", 6));
	return (write(STDERR_FILENO, str, ft_strlen(str)));
}
