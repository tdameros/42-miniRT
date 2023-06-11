/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:05:21 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/20 18:05:23 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "math/vector.h"
#include "ray_tracer/rays.h"
#include "scene.h"
#include "object.h"
#include "ray_tracer/lights.h"
#include "engine.h"

static t_color		render_pixel(t_engine *engine, int x, int y);
static t_vector3f	render_ray(t_ray ray, const t_scene *scene);

void	render_raytracing(t_engine *minirt)
{
	t_image			*img;
	unsigned int	color;
	int				y;
	int				x;

	img = &minirt->ray_traced_image;
	y = 0;
	x = 0;
	while (y < img->height)
	{
		while (x < img->width)
		{
			color = vec_rgb_to_uint(render_pixel(minirt, x, y));
			put_pixel_on_image(img, y, x, color);
			x++;
		}
		x = 0;
		y++;
	}
}

static t_color	render_pixel(t_engine *engine, int x, int y)
{
	const t_ray	ray = engine->camera.rays[x + y
		* (int) engine->camera.viewport.size.x];
	t_vector3f	pixel_color;

	pixel_color = render_ray(ray, &engine->scene);
	pixel_color = vector3f_clamp(pixel_color, 0, 1);
	pixel_color = vector3f_multiply(pixel_color, 255);
	return (pixel_color);
}

static t_vector3f	render_ray(t_ray ray, const t_scene *scene)
{
	t_hit			ray_hit;
	const t_object		*object;
	t_vector3f		result;
	t_vector3f		color;
	float			light_intensity;
	float			multiplier = 1.0f;
	int				bounces_per_pixel = 2;

	result = vector3f_create(0, 0, 0);
	for (int i = 0; i < bounces_per_pixel; i++)
	{
		ray_hit = calculate_ray_intersection(&ray, scene);
		if (!ray_hit.hit)
			return (vector3f_add(result, vector3f_multiply(scene->sky_color, multiplier)));
		object = ray_hit.object;

		// Lights
		light_intensity = calculate_light_intensity(scene, ray_hit);
		light_intensity *= multiplier;

		// Color
		color = vector3f_multiply(object->albedo, light_intensity);
		result = vector3f_add(result, color);
		multiplier *= 0.1f;
		ray.origin = vector3f_add(ray_hit.position, vector3f_multiply(ray_hit.normal, 0.0001f));
		ray.direction = reflect(ray.direction, ray_hit.normal);
	}
	return (result);
}
