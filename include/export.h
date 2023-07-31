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

int	export_image_to_ppm(const t_image *image, const char *output_file);
int	take_screenshot(const t_image *image);
int	export_scene(const t_engine *engine, const char *output_file);
int	write_object(const t_object object, int fd);
int	write_material(t_material material, int fd);

#endif