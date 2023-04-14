/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_position_in_code.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 22:16:00 by vfries            #+#    #+#             */
/*   Updated: 2023/03/08 22:16:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_position_in_code(const char *file, const char *function,
			const int line)
{
	ft_printf("file: %s%s%s, function %s%s()%s, line %s%d%s\n", RED, file,
		RESET_COLOR, GREEN, function, RESET_COLOR, PURPLE, line, RESET_COLOR);
}
