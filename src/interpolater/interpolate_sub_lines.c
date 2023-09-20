#include "threads.h"
#include "interpolater.h"

static void	draw_extra_sub_lines(void *arg,
				t_interpolater_routines_arg *data);
static void	interpolate_vertical_line(t_color *pixel,
				t_interpolater_routines_arg *data);

void	*interpolate_sub_lines(void *arg)
{
	t_interpolater_routines_arg	*data;
	t_color						*pixel;
	const t_color				*line_limit;

	data = get_routine_data(arg);
	mutex_lock(arg);
	while (data->next_line + data->incrementer * data->pixels->width
		< data->limit)
	{
		pixel = data->next_line;
		data->next_line += data->incrementer * data->pixels->width;
		mutex_unlock(arg);
		line_limit = pixel + data->pixels->width;
		while (pixel < line_limit)
			interpolate_vertical_line(pixel++, data);
		mutex_lock(arg);
	}
	if (data->first_thread_finished == false)
		draw_extra_sub_lines(arg, data);
	else
		mutex_unlock(arg);
	return (NULL);
}

static void	draw_extra_sub_lines(void *arg,
				t_interpolater_routines_arg *data)
{
	t_color			*pixel;
	const int		last_calculated_line_y = data->incrementer
		* ((data->pixels->height - 1) / data->incrementer);
	t_color			*last_calculated_line;
	const t_color	*calculated_line_cursor;
	const t_color	*line_limit;

	data->first_thread_finished = true;
	mutex_unlock(arg);
	last_calculated_line = data->pixels->data + last_calculated_line_y
		* data->pixels->width;
	pixel = last_calculated_line + data->pixels->width;
	while (pixel < data->limit)
	{
		calculated_line_cursor = last_calculated_line;
		line_limit = pixel + data->pixels->width;
		while (pixel < line_limit)
			*pixel++ = *calculated_line_cursor++;
	}
}

static void	interpolate_vertical_line(t_color *pixel,
				t_interpolater_routines_arg *data)
{
	const float	size = data->incrementer * data->pixels->width;
	t_color		*last_pixel;
	int			i;
	t_color		color;

	last_pixel = pixel + data->incrementer * data->pixels->width;
	i = data->pixels->width;
	while (i < size)
	{
		color = vector3f_multiply(*pixel, (size - i) / size);
		pixel[i] = vector3f_add(color,
				vector3f_multiply(*last_pixel, i / size));
		i += data->pixels->width;
	}
}
