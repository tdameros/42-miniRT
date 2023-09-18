#ifndef MLX_WRAPPER_H
# define MLX_WRAPPER_H

# include "engine.h"

t_vector2i	get_mouse_position(t_engine *engine);
void		get_screen_size(t_engine *engine);
int			mouse_move(t_engine *engine, t_vector2i position);
int			mouse_hide(t_engine *engine);
int			mouse_show(t_engine *engine);
void		put_image(t_engine *engine, t_image *image, t_vector2i position);

#endif