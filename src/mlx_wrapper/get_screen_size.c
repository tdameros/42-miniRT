#include "mlx.h"

#include "engine.h"

#ifndef X_SCREEN_SIZE
# define X_SCREEN_SIZE -1
#endif
#ifndef Y_SCREEN_SIZE
# define Y_SCREEN_SIZE -1
#endif

#ifdef __APPLE__

void	get_screen_size(t_engine *engine)
{
	 // TODO check that screen size is not too small
	if (X_SCREEN_SIZE <= 0 || Y_SCREEN_SIZE <= 0)
		get_screen_size_macos(&engine->window.size.x, &engine->window.size.y);
	if (X_SCREEN_SIZE > 0)
		engine->window.size.x = X_SCREEN_SIZE;
	if (Y_SCREEN_SIZE > 0)
		engine->window.size.y = Y_SCREEN_SIZE;
}
#endif
#ifdef __linux__


void	get_screen_size(t_engine *engine)
{
	 // TODO check that screen size is not too small
	if (X_SCREEN_SIZE <= 0 || Y_SCREEN_SIZE <= 0)
	{
		mlx_get_screen_size(engine->window.mlx, &engine->window.size.x, &engine->window.size.y);
		engine->window.size.y -= 70;
	}
	if (X_SCREEN_SIZE > 0)
		engine->window.size.x = X_SCREEN_SIZE;
	if (Y_SCREEN_SIZE > 0)
		engine->window.size.y = Y_SCREEN_SIZE;
}
#endif
