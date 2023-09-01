#include "ft_time.h"

float	ft_get_time_elapsed_in_seconds(const struct timeval start_time)
{
	const struct timeval	current_time = ft_get_current_time();
	float					time_elapsed_in_seconds;

	time_elapsed_in_seconds = current_time.tv_sec - start_time.tv_sec;
	time_elapsed_in_seconds
		+= (float)(current_time.tv_usec - start_time.tv_usec)
		/ (float)NB_OF_USECONDS_IN_A_SECOND;
	return (time_elapsed_in_seconds);
}
