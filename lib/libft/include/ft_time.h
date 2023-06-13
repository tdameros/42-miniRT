#ifndef FT_TIME_H
# define FT_TIME_H

# include <sys/time.h>

# define NB_OF_USECONDS_IN_A_SECOND 1000000
# define NB_OF_USECONDS_IN_A_MILLISECOND 1000

struct timeval	get_current_time(void);
char			*get_number_of_fps_in_string(struct timeval start_time);

#endif //FT_TIME_H
