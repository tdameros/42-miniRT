/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_float.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:19:18 by vfries            #+#    #+#             */
/*   Updated: 2023/04/21 03:19:18 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "libft.h"

int	get_float(char *float_string, float *float_destination)
{
	const float	float_value = ft_atof(float_string);

	if (errno == ERANGE || errno == EINVAL)
		return (-1);
	*float_destination = float_value;
	return (0);
}
