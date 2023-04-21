#ifndef T_OBJECT_H
# define T_OBJECT_H

# include <stddef.h>

# include "struct/t_vector_3d.h"
# include "struct/t_color.h"

enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
};

typedef struct s_object
{
	enum e_object_type	type;
	t_vector_3d	position;
	t_color 	color;
	double		diameter;
	double		height;
	t_vector_3d	normal;
}	t_object;

typedef struct s_objects
{
	t_object			*data;
	size_t				length;
	size_t				size;
}	t_objects;

#endif //T_OBJECT_H
