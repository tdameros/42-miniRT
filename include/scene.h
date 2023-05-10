/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:40:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/07 15:40:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "libft.h"

# include "object.h"

typedef struct s_scene {
	t_objects	objects;
}	t_scene;

t_scene	*scene_create(void);
//int		scene_add_sphere(t_scene *scene, t_sphere *sphere);

#endif