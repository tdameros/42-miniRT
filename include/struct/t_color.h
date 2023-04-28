#ifndef T_COLOR_H
#define T_COLOR_H

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

unsigned int	rgb_to_uint(t_color color);

#endif //T_COLOR_H
