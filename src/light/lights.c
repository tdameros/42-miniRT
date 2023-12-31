/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 23:08:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/25 19:53:44 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "light.h"

int	initialize_lights_array(t_lights *lights, size_t size)
{
	if (size == 0)
		size = 1;
	lights->data = malloc(sizeof(*lights->data) * size);
	if (lights->data == NULL)
		return (-1);
	lights->size = size;
	lights->length = 0;
	return (0);
}

int	add_light_in_lights(t_lights *lights, t_light light)
{
	t_light	*temp;

	if (lights->size == 0)
		if (initialize_lights_array(lights, 10) < 0)
			return (-1);
	if (lights->length < lights->size)
		lights->data[lights->length] = light;
	else
	{
		temp = malloc(sizeof(*lights->data) * (lights->size * 2));
		if (temp == NULL)
			return (-1);
		ft_memmove(temp, lights->data, sizeof(*lights->data) * lights->length);
		temp[lights->length] = light;
		free(lights->data);
		lights->data = temp;
		lights->size *= 2;
	}
	lights->length += 1;
	return (0);
}

int	remove_light_in_lights(t_lights *lights, size_t index)
{
	if (lights->length <= index)
		return (-1);
	free(lights->data[index].name);
	lights->data[index] = lights->data[lights->length - 1];
	lights->length -= 1;
	return (0);
}

void	free_light(t_light *light)
{
	free(light->name);
	ft_bzero(light, sizeof(*light));
}

int	free_lights(t_lights *lights)
{
	while (lights->length--)
		free_light(&lights->data[lights->length]);
	free(lights->data);
	lights->size = 0;
	lights->length = 0;
	return (0);
}
