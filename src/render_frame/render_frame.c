#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#include "mlx.h"
#include "libft.h"

#include "struct/t_minirt.h"
#include "struct/t_gui_box.h"
#include "render_frame.h"

int	render_frame(t_minirt *minirt)
{
	struct timeval	start_time;
	gettimeofday(&start_time, NULL);
	if (start_time.tv_usec > 1000000)
	{
		start_time.tv_sec += start_time.tv_usec / 1000000;
		start_time.tv_usec = start_time.tv_usec % 1000000;
	}

	// Do ray tracing on minirt->main_image.image
	mlx_put_image_to_window(minirt->window.mlx, minirt->window.window,
							minirt->main_image.data, 0, 0);
	render_user_interface(minirt);


	struct timeval	end_time;
	gettimeofday(&end_time, NULL);
	if (end_time.tv_usec > 1000000)
	{
		end_time.tv_sec += end_time.tv_usec / 1000000;
		end_time.tv_usec = end_time.tv_usec % 1000000;
	}
	double elasped_ms = (double)end_time.tv_usec - (double)start_time.tv_usec
						+ 1000000.0 * ((double)end_time.tv_sec - (double)start_time.tv_sec);
	int		fps = round(1.0 / ((double)elasped_ms / 1000000.0));
	char	*fps_string = ft_itoa(fps);
	mlx_string_put(minirt->window.mlx, minirt->window.window, 40, 40, 0xFF0000, fps_string);
	free(fps_string);
	return (0);
}
