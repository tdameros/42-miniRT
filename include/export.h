/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 02:38:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/31 02:38:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

# include "engine.h"

# define SCENES_PATH "assets/scenes"
# define SCREENSHOTS_PATH "assets/screenshots"

//	scene/datetime.c
int	export_scene_with_datetime(const t_engine *engine);

//	scene/material.c
int	write_material(t_material material, int fd);

//	scene/object.c
int	write_object(const t_object object, int fd);

//	scene/scene.c
int	export_scene(const t_engine *engine, const char *output_file);

//	image_to_ppm.c
int	export_image_to_ppm(const t_image *image, const char *output_file);

//	screenshot.c
int	take_screenshot(const t_image *image);

#endif