/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:24:55 by vfries            #+#    #+#             */
/*   Updated: 2023/04/21 03:24:56 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "libft.h"

# include "struct/t_gui_box.h"
# include "struct/t_minirt.h"
# include "struct/t_rt_file_requirements.h"

int				init_gui_boxes(t_minirt *minirt);
bool			mouse_is_hovering_box(t_gui_box *self,
					t_point_int_2d mouse_position);
t_point_int_2d	get_mouse_position(t_gui_box *self, t_minirt *minirt,
					int x_offset, int y_offset);

int				init_main_gui_box(t_minirt *minirt, t_gui_box *gui_box);
int				init_menu_gui_box(t_minirt *minirt, t_gui_box *gui_box,
					t_gui_box *parent);
void			icon_box_draw_method(t_gui_box *self, t_minirt *minirt,
					int x_offset, int y_offset);
int				init_settings_icon(t_minirt *minirt, t_gui_box *gui_box);

int				init_object_modification_gui_box(t_minirt *minirt,
					t_gui_box *gui_box, const t_gui_box *object_creation_gui_box);
int				init_base_color_box(t_minirt *minirt, t_gui_box *gui_box,
					t_gui_box *parent);
int				get_increasing_color(double color, double x, double decal,
					double ratio);
int				get_decreasing_color(double color, double x, double decal,
					double ratio);
int				get_base_color(double color, double x, double decal, double ratio);
int				init_color_picker_box(t_minirt *minirt, t_gui_box *gui_box,
					t_gui_box *parent);
void			add_hover_color_circle(t_gui_box *self, t_minirt *minirt,
					int x_offset, int y_offset);

int		add_object_to_object_list(t_list **object_list, t_object object);
int		error(const char *error_message);
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
