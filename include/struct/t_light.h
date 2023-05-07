#ifndef T_LIGHT_H
#define T_LIGHT_H

typedef struct s_light
{
	t_vector3	position;
	double		brightness;
	t_color		color;
}	t_light;

#endif //T_LIGHT_H
