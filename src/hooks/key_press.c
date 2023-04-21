#include "libft.h" // TODO remove when stop using

#include "miniRT_X11.h"
#include "struct/t_minirt.h"
#include "close_miniRT.h"

int	key_press_handler(int key_code, t_minirt *minirt)
{
	ft_printf("key_code == %d\n\n", key_code);
	if (key_code == KEY_ESC)
		close_minirt(minirt);
	if (key_code == KEY_H)
		minirt->gui.is_hidden = !minirt->gui.is_hidden;
	return (0);
}
