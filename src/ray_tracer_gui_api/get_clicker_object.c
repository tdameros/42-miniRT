/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_clicker_object.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 22:54:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/29 22:54:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer_gui_api.h"
#include "object.h"
#include "ray_tracer/hit.h"
#include "engine.h"


t_object	*get_clicked_object(t_engine *engine, int x, int y)
{
	const t_ray	*ray = engine->camera.rays + x
		+ (engine->ray_traced_image.height - y - 1)
		* engine->ray_traced_image.width;
	const t_hit	ray_hit = trace_ray(*ray, &engine->scene);

	if (!ray_hit.hit)
		return (NULL);
	return (engine->scene.objects.data + ray_hit.object_index);
}
