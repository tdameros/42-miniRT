#ifndef FT_TIME_H
# define FT_TIME_H

# include <sys/time.h>

# define NB_OF_USECONDS_IN_A_SECOND 1000000
# define NB_OF_USECONDS_IN_A_MILLISECOND 1000

struct timeval	ft_get_current_time(void);
int				ft_get_number_of_fps(struct timeval start_time);

#endif //FT_TIME_H
