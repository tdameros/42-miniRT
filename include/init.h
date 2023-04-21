#ifndef INIT_H
# define INIT_H

# include "libft.h"

# include "struct/t_gui_box.h"
# include "struct/t_minirt.h"
#include "struct/t_rt_file_requirements.h"

int	init_gui_boxes(t_minirt *minirt);
int	init_object_creation_gui_box(t_minirt *minirt, t_gui_box *gui_box);
int	init_object_modification_gui_box(t_minirt *minirt, t_gui_box *gui_box,
		const t_gui_box *object_creation_gui_box);

int		add_object_to_object_list(t_list **object_list, t_object object);
int		get_color(char *color_string, t_color *color_destination);
int		get_double(char *double_string, double *double_destination);
int		get_lighting_ratio(char *lighting_ratio_string,
			double *lighting_ratio_destination);
int		get_normalized_vector(char *vector_string,
			t_vector_3d *vector_destination);
int		get_position(char *position_string, t_vector_3d *position_destination);

void	invalid_scene_content_line(char **scene_content_line);
int		parse_ambient_light(t_minirt *minirt, char **scene_content_line,
			t_rt_file_requirements *rt_file_requirements, t_list **object_list);
int		parse_camera(t_minirt *minirt, char **scene_content_line,
			t_rt_file_requirements *rt_file_requirements, t_list **object_list);
int		parse_light(t_minirt *minirt, char **scene_content_line,
			t_rt_file_requirements *rt_file_requirements, t_list **object_list);
int 	parse_sphere(t_minirt *minirt, char **scene_content_line,
			t_rt_file_requirements *rt_file_requirements, t_list **object_list);
int		parse_plane(t_minirt *minirt, char **scene_content_line,
			t_rt_file_requirements *rt_file_requirements, t_list **object_list);
int		parse_cylinder(t_minirt *minirt, char **scene_content_line,
			t_rt_file_requirements *rt_file_requirements, t_list **object_list);

void	free_scene_content(char ***scene_content);
char	***get_scene_content(int fd);
int		parse_scene_content(t_minirt *minirt, char ***scene_content);
int		parse_scene(t_minirt *minirt, const char *start_up_scene);

#endif //INIT_H
