#include <stddef.h>

#include "libft.h"
#include "mlx.h"

#include "miniRT.h"
#include "miniRT_X11.h"
#include "hooks.h"
#include "struct/t_minirt.h"
#include "render_frame.h"
#include "close_miniRT.h"

static void	init_hooks(t_minirt *minirt);

int	init_minirt(t_minirt *minirt, const char *start_up_scene)
{
	ft_bzero(minirt, sizeof(t_minirt));
	minirt->window.mlx = mlx_init();
	if (minirt->window.mlx == NULL)
		return (-1);
	minirt->window.window = mlx_new_window(minirt->window.mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "miniRT");
	if (minirt->window.window == NULL)
		return (-1); // TODO: free mlx

	(void)start_up_scene;

	init_hooks(minirt);
	return (0);
}

static void	init_hooks(t_minirt *minirt)
{
	mlx_hook(minirt->window.window, KEY_PRESS, KEY_PRESS_MASK,
		&key_press_handler, minirt);
//	mlx_hook(minirt->window.window, KEY_RELEASE, KEY_RELEASE_MASK,
//		&key_release_handler, minirt);
	mlx_hook(minirt->window.window, BUTTON_PRESS, BUTTON_PRESS_MASK,
		&button_press_handler, minirt);
	mlx_hook(minirt->window.window, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK,
		&close_minirt, minirt);
	mlx_loop_hook(minirt->window.mlx, &render_frame, minirt);
}
