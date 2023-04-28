#ifndef T_COLOR_H
#define T_COLOR_H

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

unsigned int	rgb_to_uint(t_color color);
t_color			get_t_color_from_uint(unsigned int color);

#endif //T_COLOR_H
