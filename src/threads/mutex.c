/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:52:43 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/23 22:52:44 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "threads_private_header.h"

void	mutex_lock(void *routine_arg_void)
{
	t_routine_arg	*routine_arg;

	routine_arg = routine_arg_void;
	if (routine_arg->use_mutex)
		pthread_mutex_lock(&routine_arg->mutex);
}

void	mutex_unlock(void *routine_arg_void)
{
	t_routine_arg	*routine_arg;

	routine_arg = routine_arg_void;
	if (routine_arg->use_mutex)
		pthread_mutex_unlock(&routine_arg->mutex);
}
