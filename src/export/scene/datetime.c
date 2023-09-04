/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datetime.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 22:29:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/02 22:29:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "export.h"

static int	export_scene_with_datetime_and_free_output(const t_engine *engine,
				char *output_file);

int	export_scene_with_datetime(const t_engine *engine,
							const char *path_to_minirt_folder)
{
	time_t		raw_time;
	struct tm	time_info;
	char		*scene_name;
	char		*raw_scene_path;
	size_t		raw_scene_size;

	time(&raw_time);
	localtime_r(&raw_time, &time_info);
	raw_scene_path = ft_strjoin(path_to_minirt_folder,
			"/"SCENES_PATH"/Scene %Y-%m-%d at %H.%M.%S.rt");
	if (raw_scene_path == NULL)
		return (-1);
	raw_scene_size = ft_strlen(raw_scene_path);
	scene_name = malloc(sizeof(*scene_name)
			* (raw_scene_size + 20));
	if (scene_name == NULL)
	{
		free(raw_scene_path);
		return (-1);
	}
	strftime(scene_name, raw_scene_size + 20,
		raw_scene_path, &time_info);
	free(raw_scene_path);
	return (export_scene_with_datetime_and_free_output(engine, scene_name));
}

static int	export_scene_with_datetime_and_free_output(const t_engine *engine,
													char *output_file)
{
	const int	result = export_scene(engine, output_file);

	free(output_file);
	return (result);
}
