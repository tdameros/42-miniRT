/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 08:10:57 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/31 08:10:58 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include <stdlib.h>

# include "math/vector.h"
# include "colors.h"

typedef struct s_light
{
	t_vector3f	position;
	t_vector3f	color;
	float		brightness;
	t_vector3f	emitted_color;
	char		*name;
}	t_light;

typedef struct s_lights
{
	t_light		*data;
	size_t		length;
	size_t		size;
}	t_lights;

//	light.c
t_light	light_create(const t_vector3f position, const t_vector3f color,
			const float brightness);
void	light_calculate_cache(t_light *light);
void	light_set_position(t_light *light, const t_vector3f position);
void	light_set_color(t_light *light, const t_vector3f color);
void	light_set_brightness(t_light *light, const float brightness);

//	lights.c
int		initialize_lights_array(t_lights *lights, size_t size);
int		add_light_in_lights(t_lights *lights, t_light light);
int		remove_light_in_lights(t_lights *lights, size_t index);
void	free_light(t_light *light);
int		free_lights(t_lights *lights);

#endif
