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

int	take_screenshot(const t_image *image)
{
	time_t		raw_time;
	struct tm	*time_info;
	char		screenshot_name[50];

	time(&raw_time);
	time_info = localtime(&raw_time);
	strftime(screenshot_name, 50, "Screenshot %Y-%m-%d at %H.%M.%S.ppm",
		time_info);
	return (export_image_to_ppm(image, screenshot_name));
}
