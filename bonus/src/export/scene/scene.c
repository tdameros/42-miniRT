/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 08:06:38 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/31 08:06:41 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>

#include "scene.h"
#include "engine.h"
#include "export.h"

static int	write_main_elements(const t_engine *engine, int fd);
static int	write_lights(const t_engine *engine, int fd);
static int	write_objects(const t_engine *engine, const int fd);
static int	close_error(int fd);

int	export_scene(const t_engine *engine, const char *output_file)
{
	const int		fd = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);

	if (fd < 0)
		return (-1);
	if (write_main_elements(engine, fd) < 0)
		return (close_error(fd));
	if (write_lights(engine, fd) < 0)
		return (close_error(fd));
	if (dprintf(fd, "\n") < 0)
		return (close_error(fd));
	if (write_objects(engine, fd) < 0)
		return (close_error(fd));
	return (close(fd));
}

static int	write_main_elements(const t_engine *engine, int fd)
{
	const t_camera	camera = engine->camera;
	const t_light	ambient_light = engine->scene.ambient_light;
	ssize_t			return_code;

	return_code = dprintf(fd, "C\t%f,%f,%f\t%f,%f,%f\t%f\n\n",
			camera.position.x,
			camera.position.y,
			camera.position.z,
			camera.direction.x,
			camera.direction.y,
			camera.direction.z,
			camera.horizontal_fov);
	if (return_code < 0)
		return (-1);
	return_code = dprintf(fd, "A\t%f\t%f,%f,%f\n",
			ambient_light.brightness,
			ambient_light.color.x * 255.f,
			ambient_light.color.y * 255.f,
			ambient_light.color.z * 255.f);
	if (return_code < 0)
		return (-1);
	return (0);
}

static int	write_lights(const t_engine *engine, int fd)
{
	t_lights	lights;
	t_light		light;
	size_t		i;
	ssize_t		return_code;

	i = 0;
	lights = engine->scene.lights;
	while (i < lights.length)
	{
		light = lights.data[i];
		return_code = dprintf(fd, "L\t%f,%f,%f\t%f\t%f,%f,%f\n",
				light.position.x,
				light.position.y,
				light.position.z,
				light.brightness,
				light.color.x * 255.f,
				light.color.y * 255.f,
				light.color.z * 255.f);
		if (return_code < 0)
			return (-1);
		i++;
	}
	return (0);
}

static int	write_objects(const t_engine *engine, const int fd)
{
	t_objects	objects;
	t_object	object;
	size_t		i;
	ssize_t		return_code;

	i = 0;
	objects = engine->scene.objects;
	while (i < objects.length)
	{
		object = objects.data[i];
		return_code = write_object(object, fd);
		if (return_code < 0)
			return (-1);
		return_code = write_material(object.material, fd);
		if (return_code < 0)
			return (-1);
		i++;
	}
	return (0);
}

static int	close_error(int fd)
{
	close(fd);
	return (-1);
}
