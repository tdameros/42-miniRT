#include "mlx.h"

#include "engine.h"

#ifdef __APPLE__

int	mouse_move(t_engine *engine, t_vector2i position)
{
	return (mlx_mouse_move(engine->window.window, position.x, position.y));
	(void)engine;
}
#endif
#ifdef __linux__

int	mouse_move(t_engine *engine, t_vector2i position)
{
	return (mlx_mouse_move(engine->window.mlx, engine->window.window, position.x, position.y));
}
#endif
