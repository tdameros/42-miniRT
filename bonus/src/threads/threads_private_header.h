/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_private_header.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:52:56 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/23 22:53:07 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_PRIVATE_HEADER_H
# define THREADS_PRIVATE_HEADER_H

# include <pthread.h>
# include <stdbool.h>

# define NB_OF_THREADS 16

typedef struct s_routine_arg
{
	pthread_mutex_t	mutex;
	bool			use_mutex;
	void			*data;
}	t_routine_arg;

#endif
