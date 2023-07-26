/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:08:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/09 23:08:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "light.h"

t_light	light_create(const t_vector3f position, const t_vector3f color,
					const float brightness)
{
	t_light	light;

	light.position = position;
	light.color = vector3f_clamp(color, 0, 1);
	light.brightness = brightness;
	light.name = ft_strdup("Light");

	light_calculate_cache(&light);
	return (light);
}

void	light_calculate_cache(t_light *light)
{
	light->emitted_color = vector3f_clamp(vector3f_multiply(light->color,
				light->brightness), 0, 1);
}

void	light_set_position(t_light *light, const t_vector3f position)
{
	light->position = position;
	light_calculate_cache(light);
}

void	light_set_color(t_light *light, const t_vector3f color)
{
	light->color = color;
	light_calculate_cache(light);
}

void	light_set_brightness(t_light *light, const float brightness)
{
	light->brightness = brightness;
	light_calculate_cache(light);
}