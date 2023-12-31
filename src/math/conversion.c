/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:41:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/04 13:41:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

float	convert_degrees_to_radians(float degree)
{
	return (degree * (float)M_PI / 180.f);
}

float	convert_radians_to_degrees(float radians)
{
	return (radians * 180.f / (float)M_PI);
}
