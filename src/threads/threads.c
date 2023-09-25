/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:52:33 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/23 22:52:34 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "threads_private_header.h"

static size_t	create_threads(pthread_t *threads, size_t nb_of_threads,
					t_routine_arg *routine_arg, void *(*routine)(void *));
static void		join_threads(pthread_t *threads, size_t nb_of_threads);

void	start_threads(void *arg, void *(*routine)(void *))
{
	pthread_t			threads[NB_OF_THREADS];
	t_routine_arg		routine_arg;
	size_t				nb_of_created_threads;

	routine_arg.data = arg;
	if (pthread_mutex_init(&routine_arg.mutex, NULL) != 0)
	{
		routine_arg.use_mutex = false;
		routine(&routine_arg);
		return ;
	}
	routine_arg.use_mutex = true;
	nb_of_created_threads = create_threads(threads, NB_OF_THREADS,
			&routine_arg, routine);
	if (nb_of_created_threads == 0)
	{
		if (pthread_mutex_destroy(&routine_arg.mutex) != 0)
			ft_print_error("WARNING: Mutex destroy failed.");
		routine_arg.use_mutex = false;
		routine(&routine_arg);
		return ;
	}
	join_threads(threads, nb_of_created_threads);
	if (pthread_mutex_destroy(&routine_arg.mutex) != 0)
		ft_print_error("WARNING: Mutex destroy failed.");
}

static size_t	create_threads(pthread_t *threads, size_t nb_of_threads,
						t_routine_arg *routine_arg, void *(*routine)(void *))
{
	size_t	nb_of_created_threads;
	size_t	i;
	int		return_code;

	nb_of_created_threads = 0;
	i = 0;
	while (i < nb_of_threads)
	{
		return_code = pthread_create(threads + nb_of_created_threads,
				NULL, routine, routine_arg);
		if (i == 0 && return_code != 0)
			return (0);
		else if (return_code == 0)
			nb_of_created_threads++;
		i++;
	}
	return (nb_of_created_threads);
}

static void	join_threads(pthread_t *threads, size_t nb_of_threads)
{
	size_t	i;

	i = 0;
	while (i < nb_of_threads)
	{
		if (pthread_join(threads[i], NULL) != 0)
			ft_print_error("WARNING: Thread join failed.");
		i++;
	}
}
