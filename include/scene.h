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
# include "deprecated/t_light.h"

typedef struct s_scene {
	t_objects	objects;
	t_light		light;
}	t_scene;

int	init_scene(t_scene *scene);

#endif