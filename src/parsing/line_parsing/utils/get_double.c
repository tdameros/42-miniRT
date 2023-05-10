/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_double.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:19:18 by vfries            #+#    #+#             */
/*   Updated: 2023/04/21 03:19:18 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "libft.h"

int	get_double(char *double_string, double *double_destination)
{
	const double	double_value = ft_atof(double_string);

	if (errno == ERANGE || errno == EINVAL)
		return (-1);
	*double_destination = double_value;
	return (0);
}
