/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_time.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:11:11 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/31 09:11:14 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

struct timeval	ft_get_current_time(void)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	if (start_time.tv_usec > 1000000)
	{
		start_time.tv_sec += start_time.tv_usec / 1000000;
		start_time.tv_usec = start_time.tv_usec % 1000000;
	}
	return (start_time);
}
