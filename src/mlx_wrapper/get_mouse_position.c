#include "mlx.h"

#include "engine.h"

#ifdef __APPLE__

t_vector2i	get_mouse_position(t_engine *engine)
{
	t_vector2i	mouse_position;

	mlx_mouse_get_pos(engine->window.window,
		&mouse_position.x, &mouse_position.y);
	return (mouse_position);
}
#endif
#ifdef __linux__

t_vector2i	get_mouse_position(t_engine *engine)
{
	t_vector2i	mouse_position;

	mlx_mouse_get_pos(engine->window.mlx, engine->window.window,
		&mouse_position.x, &mouse_position.y);
	return (mouse_position);
}
#endif
