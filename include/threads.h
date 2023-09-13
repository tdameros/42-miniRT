
#ifndef THREADS_H
# define THREADS_H

# include <pthread.h>

# define NB_OF_THREADS 16

typedef struct s_routine_arg
{
	pthread_mutex_t	mutex;
	void			*arg;
}	t_routine_arg;

//	threads.c
void	start_threads(void *arg, void *(*routine)(void *),
			void (*on_failure)(void *));

#endif
