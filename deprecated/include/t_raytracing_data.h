#ifndef T_RAYTRACING_DATA_H
# define T_RAYTRACING_DATA_H

# include "t_ambient_light.h"
# include "ray_tracer/camera.h"
# include "light.h"
# include "object.h"

typedef struct s_raytracing_data
{
	t_ambient_light	ambient_light;
	t_camera		camera;
	t_light			light;
	t_objects		objects;
}	t_raytracing_data;

#endif //T_RAYTRACING_DATA_H
