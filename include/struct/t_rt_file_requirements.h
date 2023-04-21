#ifndef MINIRT_T_RT_FILE_REQUIREMENTS_H
# define MINIRT_T_RT_FILE_REQUIREMENTS_H

# include <stdbool.h>

typedef struct s_rt_file_requirements
{
	bool	camera;
	bool	ambient_light;
	bool	light;
}	t_rt_file_requirements;

#endif //MINIRT_T_RT_FILE_REQUIREMENTS_H
