#include "libft.h" // TODO remove when stop using

#include "events.h"
#include "engine.h"
#include "close_miniRT.h"

int	key_press_handler(int key_code, t_engine *minirt)
{
	ft_printf("key_code == %d\n\n", key_code);
	if (key_code == KEY_ESC)
		close_engine(minirt);
	if (key_code == KEY_H)
		minirt->gui.is_hidden = !minirt->gui.is_hidden;
	if (key_code == KEY_W)
		camera_move_forward(&minirt->camera, 0.1);
	else if (key_code == KEY_S)
		camera_move_forward(&minirt->camera, -0.1);
	else if (key_code == KEY_A)
		camera_move_left(&minirt->camera, 0.1);
	else if (key_code == KEY_D)
		camera_move_left(&minirt->camera, -0.1);
	else if (key_code == KEY_LEFT)
		camera_rotate_left(&minirt->camera, 2);
	else if (key_code == KEY_RIGHT)
		camera_rotate_left(&minirt->camera, -2);
	else if (key_code == KEY_UP)
		camera_rotate_up(&minirt->camera, 2);
	else if (key_code == KEY_DOWN)
		camera_rotate_up(&minirt->camera, -2);
	else
		return (0);
	camera_recalculate_view(&minirt->camera);
	camera_recalculate_rays(&minirt->camera);
	return (0);
}
