/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 23:24:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/10 23:24:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "object.h"
# include "engine.h"

typedef struct s_rt_file_requirements
{
	bool	camera;
	bool	ambient_light;
//	bool	light;  // TODO add this for mandatory part
}	t_rt_file_requirements;

typedef struct s_checkerboard_parsing_data
{
	t_vector2f	size;
	t_vector3f	color;
}	t_checkerboard_parsing_data;

t_checkerboard_parsing_data	get_checkerboard_parsing_data(
								char *raw_checkerboard_data);
void						parse_cap_checkerboard(t_object *object,
								char *file);
void						parse_cap_normal_map(t_object *object, char *file);
void						parse_cap_texture(t_object *object, char *file);
void						parse_outline_checkerboard(t_object *object,
								char *file);
void						parse_outline_normal_map(t_object *object,
								char *file);
void						parse_outline_texture(t_object *object,
								char *file);
void						parse_reflection(t_object *object,
								char *reflection);
void						parse_specular(t_object *object, char *specular);

int							error(const char *error_message);
int							get_color(char *color_string,
								t_color *color_destination);
int							get_float(char *float_string,
								float *float_destination);
int							get_lighting_ratio(char *lighting_ratio_string,
								float *lighting_ratio_destination);
int							get_normalized_vector(char *vector_string,
								t_vector3f *vector_destination);
int							get_position(char *position_string,
								t_vector3f *position_destination);

void						invalid_scene_content_line(
								char **scene_content_line);
int							parse_ambient_light(t_engine *engine,
								char **scene_content_line,
								t_rt_file_requirements *rt_file_requirements);
int							parse_camera(t_engine *engine,
								char **scene_content_line,
								t_rt_file_requirements *rt_file_requirements);
int							parse_cone(t_engine *engine,
								char **scene_content_line,
								t_rt_file_requirements *rt_file_requirements);
int							parse_light(t_engine *engine,
								char **scene_content_line,
								t_rt_file_requirements *rt_file_requirements);
int							parse_material(t_engine *engine,
								char **scene_content_line,
								t_rt_file_requirements *rt_file_requirements);
int							parse_sphere(t_engine *engine,
								char **scene_content_line,
								t_rt_file_requirements *rt_file_requirements);
int							parse_plane(t_engine *engine,
								char **scene_content_line,
								t_rt_file_requirements *rt_file_requirements);
int							parse_cylinder(t_engine *engine,
								char **scene_content_line,
								t_rt_file_requirements *rt_file_requirements);

void						free_scene_content(char ***scene_content);
char						***get_scene_content(int fd);
int							parse_scene_content(t_engine *engine,
								char ***scene_content);
int							parse_scene(t_engine *engine,
								const char *start_up_scene);

#endif
