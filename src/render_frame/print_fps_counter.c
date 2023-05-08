#include <stdlib.h>

#include "libft.h"
#include "mlx.h"

#include "struct/t_minirt.h"

static bool	should_update_fps(struct timeval last_update);

void	print_fps_counter(t_minirt *minirt, const struct timeval start_time)
{
	if (should_update_fps(minirt->gui.fps.last_update))
	{
		free(minirt->gui.fps.fps_count);
		minirt->gui.fps.fps_count = get_number_of_fps_in_string(start_time);
		minirt->gui.fps.last_update = get_current_time();
	}
	mlx_string_put(minirt->window.mlx, minirt->window.window, 40, 40, 0xFF0000,
		minirt->gui.fps.fps_count);
}

static bool	should_update_fps(const struct timeval last_update)
{
	const struct timeval	current_time = get_current_time();

	return (current_time.tv_sec * NB_OF_USECONDS_IN_A_SECOND
		+ current_time.tv_usec
		- last_update.tv_sec * NB_OF_USECONDS_IN_A_SECOND - last_update.tv_usec
		> 200 * NB_OF_USECONDS_IN_A_MILLISECOND);
}
