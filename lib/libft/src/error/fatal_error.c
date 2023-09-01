/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 23:27:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/29 23:27:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <execinfo.h>

#include "ft_io.h"

void	ft_fatal_error(const char *error_message)
{
	void		*callstack[1000];
	const int	frames = backtrace(callstack, 1000);
	const char	**symbols = (const char **)backtrace_symbols(callstack, frames);
	int			i;

	ft_print_error("Error\n");
	ft_print_error(error_message);
	ft_print_error("\n");
	if (symbols != NULL)
	{
		ft_print_error("Call Stack:\n");
		i = -1;
		while (++i < frames)
		{
			ft_print_error(symbols[i]);
			ft_print_error("\n");
		}
		free(symbols);
	}
	else
		ft_print_error("Failed to get call stack\n");
	exit(EXIT_FAILURE);
}
