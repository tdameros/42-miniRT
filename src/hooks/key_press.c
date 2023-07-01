#include "libft.h" // TODO remove when stop using

#include "events.h"
#include "engine.h"
#include <printf.h>
int	key_press_handler(int key_code, t_engine *minirt)
{
//	ft_printf("key_code == %d\n\n", key_code);
	if (key_code == KEY_ESC)
		close_engine(minirt);
	if (key_code == KEY_H)
		minirt->gui.is_hidden = !minirt->gui.is_hidden;
	if (key_code == KEY_W)
		camera_move_forward(&minirt->camera, 0.4f);
	else if (key_code == KEY_S)
		camera_move_forward(&minirt->camera, -0.4f);
	else if (key_code == KEY_A)
		camera_move_left(&minirt->camera, 0.4f);
	else if (key_code == KEY_D)
		camera_move_left(&minirt->camera, -0.4f);
	else if (key_code == KEY_LEFT)
		camera_rotate_left(&minirt->camera, 4);
	else if (key_code == KEY_RIGHT)
		camera_rotate_left(&minirt->camera, -4);
	else if (key_code == KEY_UP)
		camera_rotate_up(&minirt->camera, 4);
	else if (key_code == KEY_DOWN)
		camera_rotate_up(&minirt->camera, -4);
	else if (key_code == KEY_P)
	{
		printf("Camera:\n\tPostion:\n\t\tx: %f\n\t\ty: %f\n\t\tz: %f\n\tDirection:\n\t\tx: %f\n\t\ty: %f\n\t\tz: %f\n", minirt->camera.position.x, minirt->camera.position.y, minirt->camera.position.z, minirt->camera.direction.x, minirt->camera.direction.y, minirt->camera.direction.z);
		for (size_t i = 0; i < minirt->scene.objects.length; i++) {
			print_object2(minirt->scene.objects.data[i]);
			ft_putstr_fd("\n\n", STDERR_FILENO);
		}
		return (0);
	}
	else
		return (0);
	camera_recalculate_view(&minirt->camera);
	camera_recalculate_rays(&minirt->camera);
	return (0);
}

