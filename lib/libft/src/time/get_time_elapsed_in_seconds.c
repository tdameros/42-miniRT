/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_elapsed_in_seconds.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:57:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/23 22:57:01 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"

float	ft_get_time_elapsed_in_seconds(const struct timeval start_time)
{
	const struct timeval	current_time = ft_get_current_time();
	float					time_elapsed_in_seconds;

	time_elapsed_in_seconds = current_time.tv_sec - start_time.tv_sec;
	time_elapsed_in_seconds
		+= (float)(current_time.tv_usec - start_time.tv_usec)
		/ (float)NB_OF_USECONDS_IN_A_SECOND;
	return (time_elapsed_in_seconds);
}
