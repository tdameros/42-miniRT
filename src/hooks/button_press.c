#include "libft.h" // TODO remove when stop using

#include "miniRT_X11.h"
#include "struct/t_minirt.h"

int	button_press_handler(int button, int x, int y, t_minirt *minirt)
{
	if (button != BUTTON_LEFT)
		return (0);
	ft_printf("button == %d\nx == %d\ny == %d\n\n", button, x, y);
	(void)minirt;
	return (0);
}
