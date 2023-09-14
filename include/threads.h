
#ifndef THREADS_H
# define THREADS_H

// get_routine_data.c
void	*get_routine_data(void *routine_arg_void);

// mutex.c
void	mutex_lock(void *routine_arg_void);
void	mutex_unlock(void *routine_arg_void);

//	threads.c
void	start_threads(void *arg, void *(*routine)(void *));

#endif
