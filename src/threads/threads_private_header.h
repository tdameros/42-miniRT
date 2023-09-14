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

#endif //THREADS_PRIVATE_HEADER_H
