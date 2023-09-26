/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:49:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/19 15:49:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer/rays.h"

t_hit	min_hit(t_hit hit, t_hit near_hit)
{
	if (hit.distance > 0 && (hit.distance < near_hit.distance
			|| near_hit.distance < 0))
		return (hit);
	return (near_hit);
}
