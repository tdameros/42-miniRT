/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_number_of_fps.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:11:27 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/31 09:11:27 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "ft_time.h"

int	ft_get_number_of_fps(struct timeval start_time)
{
	const struct timeval	end_time = ft_get_current_time();
	const float				elasped_ms = end_time.tv_usec - start_time.tv_usec
		+ NB_OF_USECONDS_IN_A_SECOND * (end_time.tv_sec - start_time.tv_sec);

	return (roundf(1.f / (elasped_ms / NB_OF_USECONDS_IN_A_SECOND)));
}
