/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datetime.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 22:29:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/18 03:30:39 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "engine.h"
#include "export.h"
#include "path.h"

int	export_scene_with_datetime(const t_engine *engine)
{
	time_t		raw_time;
	struct tm	time_info;
	char		scene_name[100];

	time(&raw_time);
	localtime_r(&raw_time, &time_info);
	strftime(scene_name, 100, SCENES_PATH"/Scene %Y-%m-%d at %H.%M.%S.rt",
		&time_info);
	return (export_scene(engine, scene_name));
}
