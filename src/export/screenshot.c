/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 04:42:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/31 04:42:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>

#include "engine.h"
#include "export.h"

static int	export_image_to_ppm_and_free_output(const t_image *image,
				char *output_file);

int	take_screenshot(const t_image *image, const char *path_to_minirt_folder)
{
	time_t		raw_time;
	struct tm	time_info;
	char		*screenshot_name;
	char		*raw_screenshot_path;
	size_t		raw_screenshot_size;

	time(&raw_time);
	localtime_r(&raw_time, &time_info);
	raw_screenshot_path = ft_strjoin(path_to_minirt_folder,
			"/"SCREENSHOTS_PATH"/Screenshot %Y-%m-%d at %H.%M.%S.ppm");
	if (raw_screenshot_path == NULL)
		return (-1);
	raw_screenshot_size = ft_strlen(raw_screenshot_path);
	screenshot_name = malloc(sizeof(*screenshot_name)
			* (raw_screenshot_size + 20));
	if (screenshot_name == NULL)
	{
		free(raw_screenshot_path);
		return (-1);
	}
	strftime(screenshot_name, raw_screenshot_size + 20,
		raw_screenshot_path, &time_info);
	free(raw_screenshot_path);
	return (export_image_to_ppm_and_free_output(image, screenshot_name));
}

static int	export_image_to_ppm_and_free_output(const t_image *image,
												char *output_file)
{
	const int	result = export_image_to_ppm(image, output_file);

	free(output_file);
	return (result);
}
