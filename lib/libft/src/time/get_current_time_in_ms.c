/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_time_in_ms.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:11:11 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/31 09:11:14 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"

uint64_t	ft_get_current_time_in_ms(void)
{
	const struct timeval	current_time = ft_get_current_time();

	return (ft_timeval_to_ms(current_time));
}
