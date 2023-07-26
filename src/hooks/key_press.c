#include "libft.h" // TODO remove when stop using

#include "events.h"
#include "engine.h"
#include "hooks.h"

#include <printf.h>
int	key_press_handler(int key_code, t_engine *engine)
{
	int	i;

//	ft_printf("key_code == %d\n\n", key_code);
	if (key_code == KEY_ESC)
		close_engine(engine);
	else if (key_code == KEY_H)
		toggle_gui(&engine->gui);
	else if (key_code == KEY_P)
	{
		// TODO remove this
		printf("Camera:\n\tPostion:\n\t\tx: %f\n\t\ty: %f\n\t\tz: %f\n\tDirection:\n\t\tx: %f\n\t\ty: %f\n\t\tz: %f\n", engine->camera.position.x, engine->camera.position.y, engine->camera.position.z, engine->camera.direction.x, engine->camera.direction.y, engine->camera.direction.z);
		for (size_t i = 0; i < engine->scene.objects.length; i++) {
			print_object2(engine->scene.objects.data[i]);
			ft_putstr_fd("\n\n", STDERR_FILENO);
		}
	}
	if (key_code == KEY_ESC || key_code == KEY_H || key_code == KEY_P // TODO remove key_code == KEY_P
		|| (key_code != KEY_W && key_code != KEY_S && key_code != KEY_A
			&& key_code != KEY_D && key_code != KEY_SPACE
			&& key_code != KEY_L_SHIFT && key_code != KEY_Q
			&& key_code != KEY_E))
		return (0);
	i = -1;
	while (++i < engine->pressed_keys_index)
		if (key_code == engine->pressed_keys[i])
			return (0);
	engine->pressed_keys[engine->pressed_keys_index++] = key_code;
//	camera_recalculate_view(&engine->camera);
//	camera_recalculate_rays(&engine->camera);
	return (0);
}
