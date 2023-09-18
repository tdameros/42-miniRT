#include "mlx.h"

#include "engine.h"

#ifdef __APPLE__

int	mouse_hide(t_engine *engine)
{
	return (mlx_mouse_hide());
	(void)engine;
}
#endif
#ifdef __linux__

int	mouse_hide(t_engine *engine)
{
	return (mlx_mouse_hide(engine->window.mlx, engine->window.window));
}
#endif
