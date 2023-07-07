/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_timeval_to_ms.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 00:06:00 by vfries            #+#    #+#             */
/*   Updated: 2023/07/08 00:06:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"

long long	ft_convert_timeval_to_ms(struct timeval time)
{
	return (time.tv_usec / 1000 + time.tv_sec * 1000);
}
