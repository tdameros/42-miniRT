#include "mlx.h"

#include "engine.h"


#ifdef __APPLE__

void	get_screen_size(t_engine *engine)
{
	 // TODO check that screen size is not too small
	get_screen_size_macos(&engine->window.size.x, &engine->window.size.y);
}
#endif
#ifdef __linux__

void	get_screen_size(t_engine *engine)
{
	 // TODO check that screen size is not too small
	mlx_get_screen_size(engine->window.mlx, &engine->window.size.x, &engine->window.size.y);
	engine->window.size.y -= 70;
}
#endif
