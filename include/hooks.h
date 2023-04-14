#ifndef HOOKS_H
#define HOOKS_H

# include "struct/t_minirt.h"

int	button_press_handler(int button, int x, int y, t_minirt *minirt);
int	key_press_handler(int key_code, t_minirt *minirt);

#endif //HOOKS_H
