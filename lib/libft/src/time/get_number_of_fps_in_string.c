#include <math.h>

#include "ft_numbers.h"
#include "ft_time.h"

char	*get_number_of_fps_in_string(const struct timeval start_time)
{
	const struct timeval	end_time = get_current_time();
	const float				elasped_ms = end_time.tv_usec - start_time.tv_usec
		+ 1000000 * (end_time.tv_sec - start_time.tv_sec);
	const int				fps = roundf(1.f / (elasped_ms / 1000000.f));

	return (ft_itoa(fps));
}
