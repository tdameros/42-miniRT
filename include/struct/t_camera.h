#ifndef T_CAMERA_H
#define T_CAMERA_H

#include "struct/t_vector_3d.h"

typedef struct s_camera
{
	t_vector_3d	position;
	t_vector_3d	orientation;
	double		fov;
}	t_camera;

#endif //T_CAMERA_H
