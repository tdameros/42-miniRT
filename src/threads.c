#include <pthread.h>

#include "threads.h"
#include "libft.h"

static size_t	create_threads(pthread_t *threads, size_t nb_of_threads,
					t_routine_arg *routine_arg, void *(*routine)(void *));
static void		join_threads(pthread_t *threads, size_t nb_of_threads);

void	start_threads(void *arg, void *(*routine)(void *),
						void (*on_failure)(void *))
{
	pthread_t			threads[NB_OF_THREADS];
	t_routine_arg		routine_arg;
	size_t				nb_of_created_threads;

	if (pthread_mutex_init(&routine_arg.mutex, NULL) != 0)
	{
		on_failure(arg);
		return ;
	}
	routine_arg.arg = arg;
	nb_of_created_threads = create_threads(threads, NB_OF_THREADS,
			&routine_arg, routine);
	if (nb_of_created_threads == 0)
	{
		on_failure(arg);
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
