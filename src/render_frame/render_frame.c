#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#include "mlx.h"
#include "libft.h"

#include "struct/t_minirt.h"
#include "struct/t_gui_box.h"
#include "render_frame.h"

static void	render_minirt(t_minirt *minirt);

int	render_frame(t_minirt *minirt)
{
	struct timeval	start_time;
	gettimeofday(&start_time, NULL);
	if (start_time.tv_usec > 1000000)
	{
		start_time.tv_sec += start_time.tv_usec / 1000000;
		start_time.tv_usec = start_time.tv_usec % 1000000;
	}



	render_minirt(minirt);




	struct timeval	end_time;
	gettimeofday(&end_time, NULL);
	if (end_time.tv_usec > 1000000)
	{
		end_time.tv_sec += end_time.tv_usec / 1000000;
		end_time.tv_usec = end_time.tv_usec % 1000000;
	}
	float elasped_ms = end_time.tv_usec - start_time.tv_usec
						+ 1000000 * (end_time.tv_sec - start_time.tv_sec);
	int		fps = roundf(1.f / (elasped_ms / 1000000.f));
	char	*fps_string = ft_itoa(fps);
	mlx_string_put(minirt->window.mlx, minirt->window.window, 40, 40, 0xFF0000, fps_string);
	free(fps_string);
	return (0);
}

#if defined __linux__

static void	render_minirt(t_minirt *minirt)
{
	//	 Do ray tracing on minirt->ray_traced_image.image
	if (minirt->gui.is_hidden && minirt->gui.hidden_ratio == 1.0)
		mlx_put_image_to_window(minirt->window.mlx, minirt->window.window,
								minirt->ray_traced_image.data, 0, 0);
	else
	{
		put_background(&minirt->main_image, &minirt->tmp_background);
		render_user_interface(minirt);
		mlx_put_image_to_window(minirt->window.mlx, minirt->window.window,
			minirt->main_image.data, 0, 0);
	}
}
#elif defined __APPLE__

static void	render_minirt(t_minirt *minirt)
{
	//	 Do ray tracing on minirt->ray_traced_image.image
	mlx_put_image_to_window(minirt->window.mlx, minirt->window.window,
		minirt->ray_traced_image.data, 0, 0);
	render_user_interface(minirt);
}
#else
# error "Unsuported OS"
#endif
