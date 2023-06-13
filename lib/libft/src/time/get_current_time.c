#include <sys/time.h>
#include <stddef.h>

struct timeval	get_current_time(void)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	if (start_time.tv_usec > 1000000)
	{
		start_time.tv_sec += start_time.tv_usec / 1000000;
		start_time.tv_usec = start_time.tv_usec % 1000000;
	}
	return (start_time);
}
