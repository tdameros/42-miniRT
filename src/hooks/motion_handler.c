#include "engine.h"

int	motion_handler(int x, int y, t_engine *engine)
{
	engine->mouse_position.x = x;
	engine->mouse_position.y = y;
	return (0);
}
