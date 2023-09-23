#include "mlx.h"

#include "engine.h"

#ifdef __APPLE__

int	mouse_move(t_engine *engine, t_vector2i position)
{
	if (engine->window.is_focused == false)
		return (0);
	engine->mouse_position = position;
	return (mlx_mouse_move(engine->window.window, position.x, position.y));
}
#endif
#ifdef __linux__

int	mouse_move(t_engine *engine, t_vector2i position)
{
	if (engine->window.is_focused == false)
		return (0);
	engine->mouse_position = position;
	return (mlx_mouse_move(engine->window.mlx, engine->window.window,
			position.x, position.y));
}
#endif
