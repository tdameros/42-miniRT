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

#include "ft_io.h"

void	ft_fatal_error(const char *error_message)
{
	ft_print_error("Error\n");
	ft_print_error(error_message);
	ft_print_error("\n");
	// TODO remove below
	char *test = NULL;*test = '\0';
	exit(EXIT_FAILURE);
}
