#include "mlx.h"

#include "engine.h"

#ifdef __APPLE__

int	mouse_show(t_engine *engine)
{
	return (mlx_mouse_show());
	(void)engine;
}
#endif
#ifdef __linux__

int	mouse_show(t_engine *engine)
{
	return (mlx_mouse_show(engine->window.mlx, engine->window.window));
}
#endif
