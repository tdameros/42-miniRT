/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lighting_ratio.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:19:20 by vfries            #+#    #+#             */
/*   Updated: 2023/04/21 03:19:20 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "libft.h"

int	get_lighting_ratio(const char *lighting_ratio_string,
		float *lighting_ratio_destination)
{
	const float	lighting_ratio = ft_atof(lighting_ratio_string);

	if (lighting_ratio < 0.0 || lighting_ratio > 1.0
		|| errno == ERANGE || errno == EINVAL)
		return (-1);
	*lighting_ratio_destination = lighting_ratio;
	return (0);
}
