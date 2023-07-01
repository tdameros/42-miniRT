#ifndef ENGINE_H
# define ENGINE_H

# include "deprecated/t_raytracing_data.h"
# include "gui/gui.h"
# include "image.h"
# include "ray_tracer/camera.h"
# include "scene.h"
# include "window.h"

typedef struct s_engine
{
	t_window			window;
	t_gui				gui;
	t_image				main_image;
	t_image				ray_traced_image;
	t_raytracing_data	raytracing_data;
	t_camera			camera;
	t_scene				scene;
	t_object			*object_being_placed;
	float				object_being_placed_distance;
	t_vector2i			previous_mouse_position;
}	t_engine;

int		init_engine(t_engine *engine, const char *start_up_scene);
int		close_engine(t_engine *engine);

#endif //ENGINE_H
