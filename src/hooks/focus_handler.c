#include "engine.h"
#include "mlx_wrapper.h"

int	focus_in_handler(t_engine *engine)
{
	if (engine->camera.lock == false)
		mouse_hide(engine);
	engine->window.is_focused = true;
	return (0);
}

int	focus_out_handler(t_engine *engine)
{
	if (engine->camera.lock == false)
		mouse_show(engine);
	engine->window.is_focused = false;
	return (0);
}
