/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:01:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/07 16:01:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "scene.h"
#include "object.h"

t_scene	*scene_create(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(*scene));
	if (scene == NULL)
		return (NULL);
	scene->spheres = NULL;
	return (scene);
}

int	scene_add_sphere(t_scene *scene, t_sphere *sphere)
{
	t_list	*new_node;

	new_node = ft_lstnew(sphere);
	if (new_node == NULL)
		return (-1);
	ft_lstadd_front(&scene->spheres, new_node);
	return (0);
}
