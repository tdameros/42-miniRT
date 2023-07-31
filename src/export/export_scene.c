/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 03:28:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/31 03:28:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "engine.h"

int	export_scene(t_scene *scene, t_engine *engine)
{
	int fd;

	write(fd, &engine->camera, sizeof(engine->camera));
	write(fd, &scene->sky_color, sizeof(scene->sky_color));
	write(fd, &scene->ambient_light, sizeof(scene->ambient_light));
	// write nb light
	write(fd, &scene->lights, sizeof(scene->ambient_light));
	// write nb objet
	write(fd, &scene->lights, sizeof(scene->ambient_light));
	write(material);

}